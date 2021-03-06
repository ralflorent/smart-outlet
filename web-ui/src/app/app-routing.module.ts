/**
 * Routing module of the app
 *
 * Created on October 29, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { OutletsComponent } from './outlets/outlets.component';
import { HistoryComponent } from './history/history.component';

const routes: Routes = [
  { path: 'home', component: HomeComponent },
  { path: 'outlets', component: OutletsComponent },
  { path: 'history', component: HistoryComponent },
  { path: '', redirectTo: 'home', pathMatch: 'full'},
  { path: '**', redirectTo: 'home', pathMatch: 'full'}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
