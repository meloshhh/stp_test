#pragma once

#include <afxwin.h>

class Company;

class Office
{
public:
	CString id = L"";
	CString country = L"";
	CString city = L"";
	CString street = L"";
	CString streetNumber = L"";
	CString companyId = L"";
	Company* company = nullptr;




	~Office();

	CString GetDescriptiveStr();

	static void Read(CArray<Office,Office>& offices, CString query);

	static void Create(CString country, CString city, CString street, CString streetNo,
		CString companyId);

	static void Update(Office* office,
		CString country, CString city, CString street, CString streetNo,
		CString companyId);

	static void Delete(Office* office);

	static void LoadCompany(CArray<Office, Office>& offices);

	static CString PluckCompanyIds(CArray<Office, Office>& offices);
};

