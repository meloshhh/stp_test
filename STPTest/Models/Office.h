#pragma once

#include <afxwin.h>

class Office
{
public:
	CString id = L"";
	CString country = L"";
	CString city = L"";
	CString street = L"";
	CString streetNumber = L"";
	CString companyId = L"";



	static void Read(CArray<Office,Office>& offices, CString query);

	static void Create(CString country, CString city, CString street, CString streetNo,
		CString companyId);

	static void Update(Office* office,
		CString country, CString city, CString street, CString streetNo,
		CString companyId);

	static void Delete(Office* office);
};

