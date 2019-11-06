/**
 * Data service for the API requests
 *
 * Created on October 30, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { Injectable } from '@angular/core';
import { HttpClient, HttpErrorResponse } from '@angular/common/http';
import { catchError, map } from 'rxjs/operators';
import { Observable, throwError } from 'rxjs';

import { APP } from '@shared/constants';
import { OutletDto, Outlet } from '@shared/models';
import { map as mapDto } from '@shared/utils';

@Injectable({
	providedIn: 'root'
})
export class DataService {

	constructor(private http: HttpClient) { }

    updateStatus(payload: {outlet: string, state: string|number}): Observable<Outlet | string> {
		return this.http
        	.post(`${APP.api.endpoints.UPDATE}`, payload)
            .pipe(
                map( (response: OutletDto) => mapDto(response)),
                catchError(this.handleError)
            );
    }

    getStatus(outletId?: number): Observable<Outlet[] | string> {
		return this.http
        	.get(`${APP.api.endpoints.STATUS}`)
            .pipe(
                map( (response: any) => response.data.map((e: OutletDto) => mapDto(e))),
                catchError(this.handleError)
            );
    }

    getHistory(): Observable<Outlet[] | string> {
		return this.http
        	.get(`${APP.api.endpoints.HISTORY}`)
            .pipe(
                map( (response: any) => response.data.map((e: OutletDto) => mapDto(e))),
                catchError(this.handleError)
            );
    }

	private handleError(err: HttpErrorResponse) {

        let errorMessage = '';
        if (err.error instanceof Error) {
            // A client-side or network error occurred. Handle it accordingly.
            errorMessage = `An error occurred: ${err.error.message}`;
        } else {
            // FIXME: Not the way to handle exception
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