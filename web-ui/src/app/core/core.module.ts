/**
 * Core module for core operators
 *
 * Created on November 09, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { NgModule, Optional, SkipSelf } from '@angular/core';
import { CommonModule } from '@angular/common';

import { DataService } from '@core/services';

@NgModule({
    declarations: [],
    imports: [
        CommonModule
    ],
    providers:[DataService]
})
export class CoreModule {

    constructor(@Optional() @SkipSelf() parentModule: CoreModule) {
        if (parentModule) {
            throw new Error('CoreModule has already been loaded. You should only import Core modules in the AppModule only.');
        }
    }

}
