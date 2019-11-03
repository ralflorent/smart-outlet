# Mock an API for the Webduino

The GET request that the webduino executes will expect an HTTTP response whose shape is as follows:

```
{
  "data":
  [
    {
      "outlet": "1",
      "state": "1"
    },
    {
      "outlet": "2",
      "state": "0"
    }
  ]
}
```
Therefore, we mock the HTTP response by using a local server (based on the [json-server](https://github.com/typicode/json-server) utils).

Other alternatives could be by using an online platform for the API mocking such as [mocky.io](http://www.mocky.io). For example, the same HTTP response is also available via this endpoint: [http://www.mocky.io/v2/5db98c6b3000005a005ee41e](http://www.mocky.io/v2/5db98c6b3000005a005ee41e).

## Run this local server
To run this local server:
* first, install node.js and npm
* once installed, within a shell run the command `npm install -g json-server`
* to finally start the server, run the following command: `json-sever --host [ip_address] --port [available_port] --watch mock-api.json`.

*NOTES:* Although the content of the file `mock-api.json` shows this:
```
{
  "status": {
    "data":
    [
      {
        "outlet": "1",
        "state": "1"
      },
      {
        "outlet": "2",
        "state": "1"
      }
    ]
  }
}
```
(see the additional node "status"), that does not mean it is included in the HTTP response. However, we use as a way to target the enpoint like this: `/status`. For more info, read the details on how to use `json-server`.