/**
 * App constant to be used across the entire application
 *
 * Created on October 30, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { environment as ENV } from '@env/environment';

/**
 * Partial constants for the app
 */
export const APP = {
    api: {
        ...ENV.api
    }
};