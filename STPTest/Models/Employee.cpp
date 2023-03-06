#include "Employee.h"
#include "../Program.h"
#include "Model.h"
#include "Office.h"

Employee::~Employee()
{
    if (office) delete office;
    if (headChief) delete headChief;
}

CString Employee::GetDescriptiveStr()
{
    CString ret{};
    if (id.IsEmpty()) return ret;

    ret.Format(
        L"%s, %s, %s, %s",
        id, firstName, lastName, position
    );
    return ret;
}

void Employee::Read(CArray<Employee, Employee>& employees, CString query)
{
    employees.RemoveAll();

    Program* program = static_cast<Program*>(AfxGetApp());
    CRecordset recSet(program->db);
    recSet.Open(CRecordset::forwardOnly, query, CRecordset::readOnly);

    while (!recSet.IsEOF())
    {
        Employee employee;
        recSet.GetFieldValue(L"id", employee.id);
        recSet.GetFieldValue(L"fname", employee.firstName);
        recSet.GetFieldValue(L"lname", employee.lastName);
        recSet.GetFieldValue(L"starting_date", employee.startingDate);
        recSet.GetFieldValue(L"vacation_days", employee.vacationDays);
        recSet.GetFieldValue(L"position", employee.position);
        recSet.GetFieldValue(L"office_id", employee.officeId);
        recSet.GetFieldValue(L"assigned_head_id", employee.assignedHeadId);

        employees.Add(employee);
        recSet.MoveNext();
    }
}

void Employee::Create(CString firstName, CString lastName, CString startingDate, CString vacationDays, CString position
	, CString officeId, CString assignedHeadId)
{
    Program* program = static_cast<Program*>(AfxGetApp());
    CString query;

    query.Format(
        L"INSERT INTO employees (fname, lname, starting_date, vacation_days, position, office_id, assigned_head_id) "
        L"VALUES (%s, %s, %s, %s, %s, %s, %s)",
        Model::StrOrNull(firstName),
        Model::StrOrNull(lastName),
        Model::StrOrNull(startingDate),
        Model::NumOrNull(vacationDays),
        Model::NumOrNull(position),
        Model::NumOrNull(officeId),
        Model::NumOrNull(assignedHeadId)
    );

    program->db->ExecuteSQL(query);
}

void Employee::Update(Employee* employee, CString firstName, CString lastName, CString startingDate, CString vacationDays
	, CString position, CString officeId, CString assignedHeadId)
{
    Program* program = static_cast<Program*>(AfxGetApp());
    CString query;

    if (position != employee->position // Position changing
        && employee->position == L"0" // Previous position was head chief
    )
    {
        program->db->ExecuteSQL("UPDATE employees SET assigned_head_id = NULL WHERE assigned_head_id = " + employee->id);
    }

    query.Format(
        L"UPDATE employees "
        L"SET fname = %s, lname = %s, starting_date = %s, vacation_days = %s, position = %s, office_id = %s, assigned_head_id = %s "
        L"WHERE id = %s",
        Model::StrOrNull(firstName),
        Model::StrOrNull(lastName),
        Model::StrOrNull(startingDate),
        Model::NumOrNull(vacationDays),
        Model::NumOrNull(position),
        Model::NumOrNull(officeId),
        Model::NumOrNull(assignedHeadId),
        employee->id
    );

    program->db->ExecuteSQL(query);
}

void Employee::Delete(Employee* employee)
{
    Program* program = static_cast<Program*>(AfxGetApp());

    program->db->ExecuteSQL(
        L"UPDATE employees SET assigned_head_id = NULL WHERE assigned_head_id = " + employee->id
    );

    program->db->ExecuteSQL(
        L"DELETE FROM employees WHERE id = " + employee->id
    );
}

CString Employee::PosIntToStr(int pos)
{
    switch (pos)
    {
    case 0:
        return CString(L"Head chief");
    case 1:
        return CString(L"Specialist");
    case 2:
        return CString(L"Junior");
    default:
        return CString(L"");
    }
}

void Employee::LoadOffice(CArray<Employee, Employee>& employees)
{
    CString query;
    query.Format(
        L"SELECT * FROM offices "
        L"WHERE id IN (%s)",
        PluckOfficeIds(employees)
    );
    if (PluckOfficeIds(employees).IsEmpty())
    {
        return;
    }

    CArray<Office, Office> offices;
    Office::Read(offices, query);

    for (int i = 0; i < employees.GetSize(); ++i)
    {
        for (int j = 0; j < offices.GetSize(); j++)
        {
            if (offices[j].id == employees[i].officeId)
            {
                employees[i].office = new Office(offices[j]);
                break;
            }
        }
    }
}

void Employee::LoadHeadChief(CArray<Employee, Employee>& employees)
{
    CString query;
    query.Format(
        L"SELECT * FROM employees "
        L"WHERE id IN (%s)",
        PluckHeadChiefIds(employees)
    );
    if (PluckHeadChiefIds(employees).IsEmpty())
    {
        return;
    }

    CArray<Employee, Employee> chiefs;
    Employee::Read(chiefs, query);

    for (int i = 0; i < employees.GetSize(); ++i)
    {
        for (int j = 0; j < chiefs.GetSize(); j++)
        {
            if (chiefs[j].id == employees[i].assignedHeadId)
            {
                employees[i].headChief = new Employee(chiefs[j]);
                break;
            }
        }
    }
}

CString Employee::PluckOfficeIds(CArray<Employee, Employee>& employees)
{
    CString ret;
    for (int i = 0; i < employees.GetSize(); ++i)
    {
        if (i > 0)	ret.Append(L",");
        ret.Append(employees[i].officeId);
    }
    return ret;
}

CString Employee::PluckHeadChiefIds(CArray<Employee, Employee>& employees)
{
    CString ret;
    int hits = 0;
    for (int i = 0; i < employees.GetSize(); ++i)
    {
        if (employees[i].assignedHeadId.IsEmpty()) continue;
        if (hits > 0)	ret.Append(L",");
        ret.Append(employees[i].assignedHeadId);
        ++hits;
    }
    return ret;
}
