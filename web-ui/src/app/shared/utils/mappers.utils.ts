/**
 * Static Mapper for the `Outlet` entity and dto
 *
 * Created on November 06, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
import { OutletDto, Outlet } from '@shared/models';

export function map(dto: OutletDto): Outlet {
    let date: string | Date;

    try {
        date = new Date(dto.updatedOn); // this is a headache
    } catch (error) {
        console.log('Could not parse date');
        date = dto.updatedOn;
    }

    return {
        id: dto.id,
        name: dto.outlet,
        status: dto.state === '1'? 'ON' : 'OFF',
        updatedOn: date
    };
}