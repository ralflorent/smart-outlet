import { TestBed, async } from '@angular/core/testing';
import { RouterTestingModule } from '@angular/router/testing';
import { AppComponent } from './app.component';

describe('AppComponent', () => {

    // Component view tests
    describe('Shallow integration tests', () => {

        beforeEach(async(() => {
            TestBed.configureTestingModule({
                imports: [
                    RouterTestingModule
                ],
                declarations: [
                    AppComponent
                ],
            }).compileComponents();
        }));

        it('should create the app', () => {
            const fixture = TestBed.createComponent(AppComponent);
            const app = fixture.debugElement.componentInstance;
            expect(app).toBeTruthy();
        });

    });

    // Component logic tests
    describe('Isolated unit tests', () => {

        it('No logic tests are available for this component');

    });
});
