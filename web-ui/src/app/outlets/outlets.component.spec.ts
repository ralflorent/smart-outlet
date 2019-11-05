import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { OutletsComponent } from './outlets.component';

describe('OutletsComponent', () => {
  let component: OutletsComponent;
  let fixture: ComponentFixture<OutletsComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ OutletsComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(OutletsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
