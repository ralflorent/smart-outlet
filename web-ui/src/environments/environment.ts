// This file can be replaced during build by using the `fileReplacements` array.
// `ng build --prod` replaces `environment.ts` with `environment.prod.ts`.
// The list of file replacements can be found in `angular.json`.

const apiServiceUrl: string = `http://192.168.0.104:5000/api`;

export const environment = {
    production: false,
    api: {
        BASE_URL: apiServiceUrl,
        endpoints: {
            HISTORY: `${apiServiceUrl}/outlet/history`,
            STATUS: `${apiServiceUrl}/outlet/status`,
            UPDATE: `${apiServiceUrl}/outlet/update`,
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
