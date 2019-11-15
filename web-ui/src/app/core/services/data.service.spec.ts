/**
 * `DataService` unit testing
 *
 * Created on November 15, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { async } from '@angular/core/testing';
import { of, from } from 'rxjs';

import { DataService } from './data.service';
import { Outlet } from '@shared/models';

describe('DataService', () => {

    let httpClientSpy: { get: jasmine.Spy, post: jasmine.Spy };
    let dataService: DataService;

    const outletsDummy: Array<Outlet> = [
        { id: 1, name: '1', status: 'OFF', updatedOn: new Date("Tue, 05 Nov 2019 14:20:56 GMT") },
        { id: 2, name: '2', status: 'ON', updatedOn: new Date("Tue, 05 Nov 2019 14:57:10 GMT") },
    ];

    beforeEach(async(() => {
        // spy on the `get` and `post` methods of the HttpClient service
        httpClientSpy = jasmine.createSpyObj('HttpClient', ['get', 'post']);
        dataService = new DataService(<any>httpClientSpy);
    }));

    it('should be created', () => {
        expect(dataService).toBeTruthy();
    });

    it(`should return expected outlets' status (HttpClient called once)`, (done) => {
        // dummy objects
        const expectedOutlets: Array<Outlet> = [...outletsDummy];
        const apiResponse = {
            "data": [
                {
                    "id": 1,
                    "outlet": 1,
                    "state": 0,
                    "updatedOn": "Tue, 05 Nov 2019 14:20:56 GMT"
                },
                {
                    "id": 2,
                    "outlet": 2,
                    "state": 1,
                    "updatedOn": "Tue, 05 Nov 2019 14:57:10 GMT"
                }
            ]
        };

        // given: being mocked, no true http calls are executed
        httpClientSpy.get.and.returnValue(of(apiResponse));

        // when: this attempts to call `get()` while proceeding
        dataService.getStatus().subscribe(
            data => {
                expect(data).toEqual(expectedOutlets, `expected outlets' status`);
                done();
            },
            fail
        );

        // then
        expect(httpClientSpy.get.calls.count()).toBe(1, 'one call');
    });
});
