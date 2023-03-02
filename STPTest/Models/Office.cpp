#include "Office.h"
#include "../Program.h"

void Office::ReadOffices(CArray<Office,Office>& offices, CString query)
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

        offices.Add(office);
        recSet.MoveNext();
    }
}
