/**
 * `Outlets` page for the app
 *
 * Created on October 30, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { Component, OnInit, OnDestroy } from '@angular/core';
import { ToastrService } from 'ngx-toastr';

import { DataService } from '@core/services';
import { Outlet } from '@shared/models';

const COUNTDOWN_VALUE: number = 30;

@Component({
    selector: 'so-outlets',
    templateUrl: './outlets.component.html',
    styleUrls: ['./outlets.component.scss']
})
export class OutletsComponent implements OnInit, OnDestroy {

    outlets: Array<Outlet> = [];
    errorMsg: string = '';
    loading: boolean = false;

    private downloadTimer: any;
    private counter: number;

    constructor(
        private toastr: ToastrService,
        private dataService: DataService
    ) { }

    ngOnInit(): void {
        this.loadData();
    }

    ngOnDestroy(): void {
        this.stopTimer();
    }

    toggleStatus(outlet: Outlet): void {
        if (outlet.status === 'ON') {
            outlet.status = 'OFF';
            return;
        }

        if (outlet.status === 'OFF') {
            outlet.status = 'ON';
            return;
        }
    }

    loadData(): void {
        this.loading = true;
        this.dataService.getStatus()
            .subscribe(
                (data: Outlet[]) => {
                    this.outlets = data;
                },
                (error: string) => {
                    this.loading = false;
                    this.errorMsg = error;
                    this.toastr.error('Oops! Something went wrong');
                    this.startTimer();
                },
                () => {
                    this.loading = false;
                    this.toastr.info('Data loaded successfully');
                    this.startTimer();
                }
            );
    }

    onUpdate(outlet: Outlet): void {
        this.loading = true;
        this.toggleStatus(outlet);
        const payload = {
            outlet: outlet.name,
            state: outlet.status == 'ON' ? 1 : 0
        };

        this.dataService.updateStatus(payload)
            .subscribe(
                (data: Outlet) => {
                    const index = this.outlets.findIndex(o => data.name == o.name);
                    if (0 <=index) {
                        this.outlets[index] = data;
                    }
                },
                (error: string) => {
                    this.loading = false;
                    this.errorMsg = error;
                    this.toastr.error('Oops! Something went wrong')
                },
                () => {
                    this.loading = false;
                    this.toastr.success('Data updated successfully')
                }
            );
    }

    private startTimer(): void {
        this.counter = COUNTDOWN_VALUE;

        this.downloadTimer = setInterval(() => {
            this.counter -= 1;
            if (this.counter <= 0) {
                this.stopTimer();
                this.loadData();
            }
        }, 1000);
    }

    private stopTimer(): void {
        clearInterval(this.downloadTimer);
    }
}