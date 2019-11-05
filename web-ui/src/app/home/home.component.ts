/**
 * `Home` page for the report-engine app
 *
 * Created on October 29, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.scss']
})
export class HomeComponent implements OnInit {

  readonly pageTitle: string = `Welcome to the Smart Outlet World`;

  constructor() { }

  ngOnInit(): void {}

}
