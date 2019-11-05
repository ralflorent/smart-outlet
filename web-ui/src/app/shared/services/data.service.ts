/**
 * Data service for the API requests
 *
 * Created on October 30, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { Injectable } from '@angular/core';
import { HttpClient, HttpErrorResponse } from '@angular/common/http';
import { catchError, map } from 'rxjs/operators';
import { Observable, throwError, of } from 'rxjs';

import { APP } from '@shared/constants';
import { Outlet } from '@shared/models';

@Injectable({
	providedIn: 'root'
})
export class DataService {

	private baseUrl = APP.api.BASE_URL;

	constructor(private http: HttpClient) { }

	getOutlets(): Observable<Outlet[] | string> {
		// return this.http
        // 	.get<any>(`${this.baseUrl}/outlet`);
        return of(OUTLETS).pipe( catchError(this.handleError) );
	}

	search(term: string): Observable<any> {
		// return this.http
        // 	.get<any>(`${this.baseUrl}/outlet`);
        const found: Outlet[] = OUTLETS.filter(o => o.outlet.includes(term));
        return of(found).pipe( catchError(this.handleError) );
	}

	private handleError(err: HttpErrorResponse) {

        let errorMessage = '';
        if (err.error instanceof Error) {
            // A client-side or network error occurred. Handle it accordingly.
            errorMessage = `An error occurred: ${err.error.message}`;
        } else {
            // The backend returned an unsuccessful response code.
            // The response body may contain clues as to what went wrong,
            switch(err.status) {
                case 0: errorMessage = 'The application appears to be offline'; break;
                case 400: errorMessage = `The content required to request this resource is not valid`; break;
                case 404: errorMessage = `The content requested is not found`; break;
                case 500: errorMessage = `Errors occurred while processing a request. Try later!`; break;
                default: errorMessage = `Server returned code: ${err.status}, error message is: ${err.message}`;
            }

        }
        return throwError(errorMessage);
    }
}


const OUTLETS: Array<Outlet> = [
    { id: 1, outlet: "1", state: "0", updatedOn: "Tue, 05 Nov 2014 13:44:35 GMT" },
    { id: 1, outlet: "1", state: "1", updatedOn: "Tue, 05 Nov 2015 13:44:35 GMT" },
    { id: 2, outlet: "2", state: "1", updatedOn: "Tue, 05 Nov 2016 13:44:35 GMT" },
    { id: 1, outlet: "1", state: "1", updatedOn: "Tue, 05 Nov 2017 13:44:35 GMT" },
    { id: 2, outlet: "2", state: "0", updatedOn: "Tue, 05 Nov 2018 13:44:35 GMT" },
    { id: 2, outlet: "2", state: "0", updatedOn: "Tue, 05 Nov 2019 13:44:35 GMT" },
    { id: 2, outlet: "2", state: "0", updatedOn: "Tue, 05 Nov 2020 13:44:35 GMT" },
    { id: 2, outlet: "2", state: "0", updatedOn: "Tue, 05 Nov 2021 13:44:35 GMT" },
]