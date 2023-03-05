BEGIN TRANSACTION;

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
	company_id BIGINT,
	
	CONSTRAINT company_id_foreign
	FOREIGN KEY (company_id) REFERENCES companies(id)
		ON DELETE CASCADE,
);

ALTER TABLE companies
ADD headquarters_id BIGINT;

ALTER TABLE companies
ADD CONSTRAINT headquarters_id_foreign 
	FOREIGN KEY (headquarters_id) REFERENCES offices(id);

CREATE TABLE employees (
	id BIGINT PRIMARY KEY IDENTITY(1, 1),
	fname VARCHAR(255) NOT NULL,
	lname VARCHAR(255) NOT NULL,
	starting_date DATE,
	vacation_days INT NOT NULL,
	position INT NOT NULL,
	office_id BIGINT NOT NULL,
	
	CONSTRAINT office_id_foreign
	FOREIGN KEY (office_id) REFERENCES offices(id)
		ON DELETE CASCADE,
);

ALTER TABLE employees
ADD assigned_head_id BIGINT;

ALTER TABLE employees
ADD CONSTRAINT assigned_head_id_foreign
	FOREIGN KEY (assigned_head_id) REFERENCES employees(id);
	
COMMIT;
	