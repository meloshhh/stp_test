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

	static void ReadOffices(CArray<Office,Office>& offices, CString query);
};

