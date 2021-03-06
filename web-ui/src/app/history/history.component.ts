/**
 * `History` page for the app
 *
 * Created on October 30, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { Component, OnInit, ViewChild } from '@angular/core';
import { DatePipe } from '@angular/common';
import { MatPaginator, MatTableDataSource } from '@angular/material';
import { ToastrService } from 'ngx-toastr';

import { DataService } from '@core/services';
import { Outlet } from '@shared/models';

@Component({
	selector: 'so-history',
	templateUrl: './history.component.html',
    styleUrls: ['./history.component.scss'],
    providers: [DatePipe]
})
export class HistoryComponent implements OnInit {

	outlets: Array<Outlet> = [];
	errorMsg: string = '';
	loading: boolean = false;
	dataSource: any;
    columnNames: string[] = [];
    graph: { data: Array<any>, layout: any } = { data: [], layout: null };

    @ViewChild(MatPaginator, { static: true })
    paginator: MatPaginator;

	constructor(
		private toastr: ToastrService,
        private dataService: DataService,
        private datePipe: DatePipe
	) { }

	ngOnInit(): void {
		this.loading = true;
        this.columnNames = ['name', 'status', 'updatedOn'];
        this.graph.layout = {
            title: 'Overview of historical switch ON/OFF actions',
            xaxis: { type: 'date', title: 'Date' },
            yaxis: { title: 'Number of times switched' },
            responsive: true
        };
		this.dataService.getHistory()
			.subscribe(
				(data: Outlet[]) => {
					this.outlets = data;
					this.dataSource = new MatTableDataSource<Outlet>(data);
                    this.dataSource.paginator = this.paginator;

                    // get ready for plots
                    this.graph.data['removeAll'](); // augmented Array<T>.prototype

                    Object
                        .values(this.groupOutletsByName(data))
                        .forEach(outlets =>
                            this.graph.data.push(this.prepareGraphData(outlets))
                        )
                    ;
				},
				(error: string) => {
					this.loading = false;
                    this.errorMsg = error;
                    this.toastr.error('Oops! Something went wrong')
				},
				() => {
                    this.loading = false;
                    this.toastr.info('Data loaded successfully')
                }
            );
	}

    applyFilter(term: string): void {
        term = term.trim().toLowerCase(); // clean search term
        this.dataSource.filter = term;
    }

	onReload(): void {
        this.ngOnInit(); // reload tables
    }

    private groupOutletsByName(outlets: Array<Outlet>): { [key: string]: Array<Outlet> } {
        // what are the existing names
        const result: { [key: string]: Array<Outlet> } = {};

        const availableNames: Array<string> = [];
        outlets.forEach(o => {
            if (!availableNames.includes(o.name)) // make them unique
                availableNames.push(o.name);
        });

        // group them now as: { 'name': [...outlets] }
        availableNames.forEach(name => result[name] = outlets.filter(o => o.name === name));
        return result;
    }

    private prepareGraphData(outlets: Outlet[]): any {
        if (0 >= outlets.length)
            return {};

        const sample = outlets[0];
        const data = {
            x: [],
            y: [],
            // type: 'scatter',
            // mode: 'lines+points',
            // marker: { color: `${sample.name == '1'? 'blue' : 'orange'}` },
            name: `Outlet ${sample.name}`
        };
        const days = {}; // expecting: { 'yyyy-MM-dd': 1+ }

        // group by same date ('yyyy-MM-dd')
        for (const o of outlets) {
            const day = this.datePipe.transform(o.updatedOn, 'yyyy-MM-dd');
            if ( Object.keys(days).includes(day) )
                days[day] += 1; // repeated occurrences
            else
                days[day] = 1; // first time
        }

        // accumulate switch-actions on a daily basis
        for (const day of Object.keys(days)) {
            const reps = days[day];
            data.x.push(day);
            data.y.push(reps);
        }

        return data;
    }
}
