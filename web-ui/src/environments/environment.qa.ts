/**
 * Configuration for QA environment
 *
 * Created on November 06, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
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
