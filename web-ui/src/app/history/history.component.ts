/**
 * `History` page for the app
 *
 * Created on October 30, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { Component, OnInit, ViewChild } from '@angular/core';
import { MatPaginator, MatTableDataSource } from '@angular/material';
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
	errorMsg: string = '';
	loading: boolean = false;
	dataSource: any;
	columnNames: string[] = [];
	@ViewChild(MatPaginator, { static: true }) paginator: MatPaginator;

	constructor(
		private toastr: ToastrService,
		private dataService: DataService
	) { }

	ngOnInit(): void {
		this.loading = true;
		this.columnNames = ['name', 'status', 'updatedOn'];
		this.dataService.getHistory()
			.subscribe(
				(data: Outlet[]) => {
					this.outlets = data;
					this.dataSource = new MatTableDataSource<Outlet>(data);
					this.dataSource.paginator = this.paginator;
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
        // reload tables
        this.ngOnInit();
	}
}
