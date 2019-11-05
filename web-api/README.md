# Web API service

The Web API is a service that provides resources for both the Webduino and the Web UI.

## Requirements
For this API, we use JSON format for the data traffic.

### Use cases
1. Retrieve the current outlet statuses
    * for the webduino
    * for the web-ui
2. Set an outlet status
3. Retrieve the history of the outlet statuses

### Specs
For the use case *Retrieve the current outlet statuses*, the specs are the following:

*REQUEST*:
* method: `GET`
* endpoint: `/api/outlet/status`

*RESPONSE*:
```
{
  "data":
  [
    {
      "outlet": "1",
      "state": "1",
      "updatedOn": "2019-10-04T06:00:00Z"
    },
    {
      "outlet": "2",
      "state": "0",
      "updatedOn": "2019-10-04T06:00:00Z"
    }
  ]
}
```

*ERROR*:

Not implemented yet

For the use case *Set an outlet status*, the specs are the following:

*REQUEST*:
* method: `POST`
* endpoint: `/api/outlet/status`
* body:
```
{
    "id": 1,
    "outlet": "2",
    "state": "0",
}
```

*RESPONSE*:
```
{
    "id": 1,
    "outlet": "2",
    "state": "0",
    "updatedOn": "2019-10-04T06:00:00Z"
}
```

*ERROR*:

Not implemented yet


For the use case *Retrieve the history of the outlet statuses*, the specs are the following:

*REQUEST*:
* method: `GET`
* endpoint: `/api/outlet/history`

*RESPONSE*:
```
{
  "data":
  [
    {
      "outlet": "1",
      "state": "1",
      "updatedOn": "2019-10-04T06:00:00Z"
    },
    {
      "outlet": "2",
      "state": "0",
      "updatedOn": "2019-10-04T06:00:00Z"
    },
    {
      "outlet": "2",
      "state": "1",
      "updatedOn": "2019-10-04T06:04:00Z"
    },
    ...
  ]
}
```

*ERROR*:

Not implemented yet

## Notes
* The date format used is: `2019-10-04T06:00:00Z`
* This API contains no security layers. That is, no authentication module has been implemented.
