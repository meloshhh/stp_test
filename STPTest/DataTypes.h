#pragma once

enum DBType
{
	SQLServer,
	MSAccess,
};

struct Company
{
public:
	CString id;
	CString name;
	CString createdAt;
	CString hqAddress;
};

struct Office
{
public:
	CString id;
	CString country;
	CString city;
	CString street;
	CString streetNumber;
};
