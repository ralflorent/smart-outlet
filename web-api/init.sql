CREATE DATABASE IF NOT EXISTS smart_outlet;
USE smart_outlet;

DROP TABLE IF EXISTS  connections;

CREATE TABLE IF NOT EXISTS connections (
    id MEDIUMINT NOT NULL AUTO_INCREMENT,
    -- ip varchar(255),
    outlet INT,
    state INT,
    updatedOn TIMESTAMP,
    PRIMARY KEY (id)
);