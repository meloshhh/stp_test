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


	static void Read(CArray<Company, Company>& companies, CString query);

	static void Create(CString name);

	static void Update(Company* company, CString name, Office* hq);
	
	static void Delete(Company* company);
};

