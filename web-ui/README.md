# Web UI

The Web UI module of this project is basically an Angular-based application.

## Docker container
The web application is also available as a [docker container](https://hub.docker.com/r/ralflorent/smart-outlet) for demo purposes by using an online mock API (mocky.io) to make available the API responses.

Having docker installed, an example of how to run a container of this image is:
```
docker container run --name so -p 4000:80 ralflorent/smart-outlet:1.0.0
```
Then, launch `http://localhost:4000` in your default browser.

PS: *Note that we are assuming that the chosen port 4000 is not taken already. Otherwise, change it to another available port number.*

For more info on Docker, please view this [page](https://www.docker.com/).

## Application creation
The app or web-ui is created with [Angular CLI](https://cli.angular.io/). Below is detailed the command used to do so.
```
ng new smart-outlet --routing --style scss --skip-git --prefix so --directory web-ui
```
## Components
The main components are `home`, `outlets`, and `history`. The command to create them is:
```
ng generate component home|outlets|history
```

This project was generated with [Angular CLI](https://github.com/angular/angular-cli) version 7.3.5.

## Development server

Run `ng serve` for a dev server. Navigate to `http://localhost:4200/`. The app will automatically reload if you change any of the source files.

## Code scaffolding

Run `ng generate component component-name` to generate a new component. You can also use `ng generate directive|pipe|service|class|guard|interface|enum|module`.

## Build

Run `ng build` to build the project. The build artifacts will be stored in the `dist/` directory. Use the `--prod` flag for a production build.

## Running unit tests

Run `ng test` to execute the unit tests via [Karma](https://karma-runner.github.io).

## Running end-to-end tests

Run `ng e2e` to execute the end-to-end tests via [Protractor](http://www.protractortest.org/).

## Further help

To get more help on the Angular CLI use `ng help` or go check out the [Angular CLI README](https://github.com/angular/angular-cli/blob/master/README.md).
