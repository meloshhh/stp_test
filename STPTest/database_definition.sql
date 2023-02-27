DROP TABLE IF EXISTS companies;
DROP TABLE IF EXISTS offices;
DROP TABLE IF EXISTS employees;

CREATE TABLE companies (
	id BIGINT PRIMARY KEY IDENTITY(1, 1),
	name VARCHAR(255) NOT NULL,
	created_at DATETIME NOT NULL,
);

CREATE TABLE offices (
	id BIGINT PRIMARY KEY IDENTITY(1, 1),
	country VARCHAR(255),
	city VARCHAR(255),
	street VARCHAR(255),
	street_number VARCHAR(30),
);

ALTER TABLE companies
ADD headquarters_id BIGINT;

ALTER TABLE companies
ADD FOREIGN KEY (headquarters_id) REFERENCES offices(id);
	