/**
 * `History` page for the app
 *
 * Created on October 30, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { Component, OnInit, ViewChild } from '@angular/core';
import { MatPaginator, MatSort, MatTableDataSource } from '@angular/material';
import { ToastrService } from 'ngx-toastr';

import { DataService } from '@shared/services';
import { Outlet } from '@shared/models';

@Component({
	selector: 'so-history',
	templateUrl: './history.component.html',
	styleUrls: ['./history.component.scss']
})
export class HistoryComponent implements OnInit {

	outlets: Array<Outlet> = [];
	searchTerm: string = '';
	errorMsg: string = '';
	loading: boolean = false;
	dataSource: any;
	columnNames: string[] = [];
	@ViewChild(MatPaginator, { static: true }) paginator: MatPaginator;
	@ViewChild(MatSort, { static: true }) sort: MatSort;

	constructor(
		private toastr: ToastrService,
		private dataService: DataService
	) { }

	ngOnInit() {
		this.loading = true;
		this.columnNames = ['name', 'status', 'updatedOn'];
		this.dataService.getOutlets()
			.subscribe(
				(data: Outlet[]) => {
					this.outlets = data;
					this.dataSource = new MatTableDataSource<Outlet>(data);
					this.dataSource.paginator = this.paginator;
					this.dataSource.sort = this.sort;
				},
				(error: string) => {
					this.loading = false;
					this.errorMsg = error;
				},
				() => this.loading = false
			);
	}

	search(term: string): void {
        if (!term) {
            this.errorMsg = `Please enter a valid search term to proceed`;
            this.ngOnInit();
            return;
        }

        this.errorMsg = '';
        this.loading = true;
        this.dataService.search(term)
            .subscribe(
                (data: Outlet[]) => {
                    this.outlets = data;
                    this.dataSource = new MatTableDataSource<Outlet>(data);
                    this.dataSource.paginator = this.paginator;
                    if (this.outlets && this.outlets.length) return;
                    this.errorMsg = `No results found for '${term}'`;
                },
                (error: string) => {
                    this.loading = false;
                    this.errorMsg = error;
                },
                () => this.loading = false
            );
    }

    applyFilter(term: string): void {
        term = term.trim().toLowerCase(); // clean search term
        this.dataSource.filter = term;
    }

	onReload(): void {
		// reload tables
	}
}
