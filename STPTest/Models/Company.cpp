#include "Company.h"
#include "../Program.h"
#include "Office.h"

void Company::ReadAll(CArray<Company, Company>& companies, CString query)
{
    companies.RemoveAll();

    Program* program = static_cast<Program*>(AfxGetApp());
    CRecordset recSet(program->db);
    recSet.Open(CRecordset::forwardOnly, query, CRecordset::readOnly);

    while (!recSet.IsEOF())
    {
        Company company;
        recSet.GetFieldValue(L"id", company.id);
        recSet.GetFieldValue(L"name", company.name);
        recSet.GetFieldValue(L"created_at", company.createdAt);
        recSet.GetFieldValue(L"headquarters_id", company.headquartersId);

        companies.Add(company);
        recSet.MoveNext();
    }
}

void Company::Create(CString name)
{
    Program* program = static_cast<Program*>(AfxGetApp());
    CString query;

    query.Format(
        L"INSERT INTO companies (name, created_at, headquarters_id) "
        L"VALUES ('%s', '%s')",
        name,
        CTime::GetCurrentTime().FormatGmt(L"%F %T")
    );

    program->db->ExecuteSQL(query);
}

void Company::Update(Company* company, CString name, Office* hq)
{
    if (!company) throw CString(L"Company pointer is invalid");

    Program* program = static_cast<Program*>(AfxGetApp());
    CString query;

    company->name = name;
    company->headquartersId = hq ? hq->id : L"";

    query.Format(
        L"UPDATE companies "
        L"SET name = '%s', headquarters_id = ",
        company->name
    );

    if (company->headquartersId.IsEmpty())
    {
        query.Append(L"NULL");
    }
    else
    {
        query.Append(company->headquartersId);
    }
    query.Append(L" WHERE id = " + company->id + L";");

    program->db->ExecuteSQL(query);
}
