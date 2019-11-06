// This file can be replaced during build by using the `fileReplacements` array.
// `ng build --prod` replaces `environment.ts` with `environment.prod.ts`.
// The list of file replacements can be found in `angular.json`.

// history:  http://www.mocky.io/v2/5dc2a1b12f000065004be23d
// status: http://www.mocky.io/v2/5dc2a23e2f00005b004be245
// update:  http://www.mocky.io/v2/5dc2a26a2f000050004be24a
const apiServiceUrl: string = `http://www.mocky.io/v2`;

export const environment = {
    production: false,
    api: {
        BASE_URL: apiServiceUrl,
        endpoints: {
            HISTORY: `${apiServiceUrl}/5dc2a1b12f000065004be23d`,
            STATUS: `${apiServiceUrl}/5dc2a23e2f00005b004be245`,
            UPDATE: `${apiServiceUrl}/5dc2a26a2f000050004be24a`,
        }
    }
};

/*
 * For easier debugging in development mode, you can import the following file
 * to ignore zone related error stack frames such as `zone.run`, `zoneDelegate.invokeTask`.
 *
 * This import should be commented out in production mode because it will have a negative impact
 * on performance if an error is thrown.
 */
// import 'zone.js/dist/zone-error';  // Included with Angular CLI.
