#pragma once

#include <afxwin.h>

class Office;

class Company
{
public:
	CString id = L"";
	CString name = L"";
	CString createdAt = L"";
	CString headquartersId = L"";


	static void ReadAll(CArray<Company, Company>& companies, CString query);

	static void Create(CString name);

	static void Update(Company* company, CString name, Office* hq);
};

