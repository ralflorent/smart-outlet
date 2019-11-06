/**
 * `Home` page for the report-engine app
 *
 * Created on October 30, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { Component, OnInit } from '@angular/core';
import { ToastrService } from 'ngx-toastr';

import { DataService } from '@shared/services';
import { Outlet } from '@shared/models';

@Component({
    selector: 'so-outlets',
    templateUrl: './outlets.component.html',
    styleUrls: ['./outlets.component.scss']
})
export class OutletsComponent implements OnInit {

    outlets: Array<Outlet> = [];
	errorMsg: string = '';
	loading: boolean = false;

    constructor(
		private toastr: ToastrService,
		private dataService: DataService
	) { }

    ngOnInit(): void {
		this.loading = true;
		this.dataService.getStatus()
			.subscribe(
				(data: Outlet[]) => {
					this.outlets = data;
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
}