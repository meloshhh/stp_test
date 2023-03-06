#include "Office.h"
#include "../Program.h"
#include "Model.h"
#include "Company.h"

Office::~Office()
{
    if (company) delete company;
}

CString Office::GetDescriptiveStr()
{
    CString ret{};
    if (id.IsEmpty()) return ret;

    ret.Format(
        L"%s, %s, %s, %s, %s",
        id, country, city, street, streetNumber
    );
    return ret;
}

void Office::Read(CArray<Office,Office>& offices, CString query)
{
    offices.RemoveAll();

    Program* program = static_cast<Program*>(AfxGetApp());
    CRecordset recSet(program->db);
    recSet.Open(CRecordset::forwardOnly, query, CRecordset::readOnly);

    while (!recSet.IsEOF())
    {
        Office office;
        recSet.GetFieldValue(L"id", office.id);
        recSet.GetFieldValue(L"country", office.country);
        recSet.GetFieldValue(L"city", office.city);
        recSet.GetFieldValue(L"street", office.street);
        recSet.GetFieldValue(L"street_number", office.streetNumber);
        recSet.GetFieldValue(L"company_id", office.companyId);

        offices.Add(office);
        recSet.MoveNext();
    }
}

void Office::Create(CString country, CString city, CString street, CString streetNo, CString companyId)
{
    Program* program = static_cast<Program*>(AfxGetApp());
    CString query;

    query.Format(
        L"INSERT INTO offices (country, city, street, street_number, company_id) "
        L"VALUES (%s, %s, %s, %s, %s)",
        Model::StrOrNull(country),
        Model::StrOrNull(city),
        Model::StrOrNull(street),
        Model::StrOrNull(streetNo),
        Model::NumOrNull(companyId)
    );

    program->db->ExecuteSQL(query);
}

void Office::Update(Office* office, CString country, CString city, CString street, CString streetNo, CString companyId)
{
    Program* program = static_cast<Program*>(AfxGetApp());
    CString query;

    if (companyId != office->companyId)
    {
        program->db->ExecuteSQL(
            L"UPDATE companies "
            L"SET headquarters_id = NULL "
            L"WHERE id = " + office->companyId + L" AND headquarters_id = " + office->id
        );
    }

    query.Format(
        L"UPDATE offices "
        L"SET country = %s, city = %s, street = %s, street_number = %s, company_id = %s "
        L"WHERE id = %s",
        Model::StrOrNull(country),
        Model::StrOrNull(city),
        Model::StrOrNull(street),
        Model::StrOrNull(streetNo),
        Model::NumOrNull(companyId),
        office->id
    );

    program->db->ExecuteSQL(query);
}

void Office::Delete(Office* office)
{
    Program* program = static_cast<Program*>(AfxGetApp());

    program->db->ExecuteSQL(
        L"UPDATE companies "
        L"SET headquarters_id = NULL "
        L"WHERE id = " + office->companyId
    );

    program->db->ExecuteSQL(
        L"DELETE FROM offices WHERE id = " + office->id
    );
}

void Office::LoadCompany(CArray<Office, Office>& offices)
{
    CString query;
    query.Format(
        L"SELECT * FROM companies "
        L"WHERE id IN (%s)",
        PluckCompanyIds(offices)
    );
    if (PluckCompanyIds(offices).IsEmpty())
    {
        return;
    }

    CArray<Company, Company> companies;
    Company::Read(companies, query);

    for (int i = 0; i < offices.GetSize(); ++i)
    {
        for (int j = 0; j < companies.GetSize(); j++)
        {
            if (companies[j].id == offices[i].companyId)
            {
                offices[i].company = new Company(companies[j]);
                break;
            }
        }
    }
}

CString Office::PluckCompanyIds(CArray<Office, Office>& offices)
{
    CString ret{};
    for (int i = 0; i < offices.GetSize(); i++)
    {
        if (i > 0)	ret.Append(L",");
        ret.Append(offices[i].companyId);
    }
    return ret;
}
