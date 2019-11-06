import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { NgbModule } from '@ng-bootstrap/ng-bootstrap';
import { ToastrModule } from 'ngx-toastr';
import {
    MatTableModule,
    MatPaginatorModule,
    MatInputModule,
    MatListModule,
    MatIconModule,
    MatChipsModule,
    MatSlideToggleModule
} from '@angular/material';


@NgModule({
    declarations: [],
    imports: [
        CommonModule,
        FormsModule,
        ReactiveFormsModule,
        NgbModule,
        MatTableModule,
        MatPaginatorModule,
        MatInputModule,
        MatListModule,
        MatIconModule,
        MatSlideToggleModule,
        MatChipsModule,
        ToastrModule.forRoot(
            {
                timeOut: 3000,
                positionClass: 'toast-top-right',
                preventDuplicates: true,
            }
        )
    ],
    exports: [
        CommonModule,
        FormsModule,
        ReactiveFormsModule,
        NgbModule,
        MatTableModule,
        MatPaginatorModule,
        MatInputModule,
        MatListModule,
        MatIconModule,
        MatSlideToggleModule,
        MatChipsModule,
        ToastrModule
    ]
})
export class SharedModule { }
