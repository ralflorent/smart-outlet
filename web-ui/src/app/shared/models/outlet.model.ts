/**
 * `Outlet` model entity
 *
 * Created on October 30, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */

/**
 * `Outlet` JSON-like signature
 * @property {number} id - internal id of the outlet
 * @property {string} outlet - name of the outlet (mainly id'd by the internal id)
 * @property {string|number|boolean} state - two-option state (0 | 1) to display ON / OFF
 * @property {string|Date} updatedOn - date of last update
 */
export interface Outlet {
    id: number
    outlet: string
    state: string | number | boolean
    updatedOn: string | Date
}