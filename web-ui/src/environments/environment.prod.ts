const apiServiceUrl: string = `http://192.168.0.30:8080/api`;

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
