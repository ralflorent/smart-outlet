/**
 * `OutletDto` model entity
 *
 * Created on October 30, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */

/**
 * `OutletDto` JSON-like signature
 * @property {number} id - internal id of the outlet
 * @property {string|number} outlet - name of the outlet (mainly id'd by the internal id)
 * @property {string|number} state - two-option state (0 | 1) to display ON / OFF
 * @property {string} updatedOn - date of last update
 */
export interface OutletDto {
    id: number
    outlet: string | number
    state: string | number
    updatedOn: string
}