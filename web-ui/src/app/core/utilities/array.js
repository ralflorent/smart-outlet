/**
 * Core utilities to augment `Array` functionalities
 *
 * Created on November 09, 2019
 * @author Ralph Florent <r.florent@jacobs-university.de>
 */
(function (win) {

    'use strict';

    var array = Array.prototype || win.Array.prototype;

    if (Array.prototype) {
        Object.defineProperty(array, 'removeAll', {
            value: function () {
                // 1. Let O be ? ToObject(this value).
                if (this == null) {
                    throw TypeError('"this" is null or not defined');
                }

                var o = Object(this);

                // 2. Let len be ? ToLength(? Get(O, "length")).
                var len = o.length >>> 0;

                // 3. Use built-in functions to remove items
                return o.splice(0, len);
            },
            configurable: true,
            writable: true
        });
    }

})(window);