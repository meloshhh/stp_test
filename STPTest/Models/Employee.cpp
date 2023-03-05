#include "Employee.h"
#include "../Program.h"
#include "Model.h"

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
