#include "EmployeeDialog.h"
#include "Utilities/Validator.h"
#include "SimplePopupDialog.h"
#include "DataTypes.h"

EmployeeDialog::EmployeeDialog(Employee* employee) : CDialog(IDD),
valFirstName(L""),
valLastName(L""),
valStartingDate(2023, 3, 5, 0, 0, 0),
valVacationDays(L""),
employee(employee),
offices(),
headChiefs()
{
}

EmployeeDialog::~EmployeeDialog()
{
}

void EmployeeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_E_FNAME, valFirstName);
	DDX_Text(pDX, IDC_E_LNAME, valLastName);
	DDX_DateTimeCtrl(pDX, IDC_E_SDATE, valStartingDate);
	DDX_Text(pDX, IDC_E_VACDAYS, valVacationDays);
	DDX_Control(pDX, IDC_E_POS, ctrlPosition);
	DDX_Control(pDX, IDC_E_OFFICE, ctrlOffice);
	DDX_Control(pDX, IDC_E_AHID, ctrlAssignedHeadId);
}

BOOL EmployeeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadOffices();

	if (offices.GetSize() == 0)
	{
		EndDialog(IDCANCEL);
		DISPLAY_VAL_ERR(L"You must first create at least 1 office")
	}

	ctrlPosition.AddString(L"Head chief");
	ctrlPosition.AddString(L"Specialist");
	ctrlPosition.AddString(L"Junior");
	ctrlPosition.SetCurSel(2);

	LoadHeadChiefs(offices[0].id);


	if (employee)
	{
		valFirstName = employee->firstName;
		valLastName = employee->lastName;
		valVacationDays = employee->vacationDays;
		ctrlPosition.SetCurSel(StrToInt(employee->position));
		for (int i = 0; i < offices.GetSize(); ++i)
		{
			if (offices[i].id == employee->officeId) ctrlOffice.SetCurSel(i);
		}
		valStartingDate.ParseDateTime(employee->startingDate);
		for (int i = 0; i < headChiefs.GetSize(); ++i)
		{
			if (headChiefs[i].id == employee->assignedHeadId)
			{
				ctrlAssignedHeadId.SetCurSel(i + 1);
			}
		}
		UpdateData(FALSE);
	}
	else
	{
	}


	return TRUE;
}

void EmployeeDialog::LoadOffices()
{
	CString query(
		"SELECT * "
		"FROM offices"
	);

	Office::Read(offices, query);

	for (int i = 0; i < offices.GetSize(); ++i)
	{
		ctrlOffice.AddString(offices[i].id);
	}

	if (offices.GetSize() > 0)
	{
		ctrlOffice.SetCurSel(0);
	}
}

void EmployeeDialog::LoadHeadChiefs(CString officeId)
{
	ctrlAssignedHeadId.ResetContent();
	CString query;
	query.Format(L"SELECT * FROM employees WHERE position = 0 AND office_id = %s", officeId);
	if (employee)
	{
		query.Append(L" AND id != ");   query.Append(employee->id);
	}
	Employee::Read(headChiefs, query);

	ctrlAssignedHeadId.AddString(L"/");
	for (int i = 0; i < headChiefs.GetSize(); ++i)
	{
		ctrlAssignedHeadId.AddString(headChiefs[i].id);
	}
	ctrlAssignedHeadId.SetCurSel(0);
}

void EmployeeDialog::OnOK()
{
	UpdateData(TRUE);
	int sel = ctrlOffice.GetCurSel();
	int headSel = ctrlAssignedHeadId.GetCurSel();

	CString pos; 
	pos.Format(L"%d", ctrlPosition.GetCurSel());
	if (!employee)
	{
		Employee::Create(
			valFirstName,
			valLastName,
			valStartingDate.Format(L"%F"),
			valVacationDays,
			pos,
			offices[ctrlOffice.GetCurSel()].id,
			headSel > 0 ? headChiefs[headSel - 1].id : L""
		);
	}
	else
	{
		Employee::Update(
			employee,
			valFirstName,
			valLastName,
			valStartingDate.Format(L"%F"),
			valVacationDays,
			pos,
			offices[ctrlOffice.GetCurSel()].id,
			headSel > 0 ? headChiefs[headSel - 1].id : L""
		);
	}

	EndDialog(IDOK);
}

void EmployeeDialog::OnCbnSelchangeEPos()
{
	int sel = ctrlPosition.GetCurSel();
	if (sel == 0)
	{
		ctrlAssignedHeadId.SetCurSel(0);
		ctrlAssignedHeadId.EnableWindow(FALSE);
	}
	else
	{
		ctrlAssignedHeadId.EnableWindow(TRUE);
	}
}

void EmployeeDialog::OnCbnSelchangeEOffice()
{
	int sel = ctrlOffice.GetCurSel();
	LoadHeadChiefs(offices[sel].id);
}

BEGIN_MESSAGE_MAP(EmployeeDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_E_POS, &EmployeeDialog::OnCbnSelchangeEPos)
	ON_CBN_SELCHANGE(IDC_E_OFFICE, &EmployeeDialog::OnCbnSelchangeEOffice)
END_MESSAGE_MAP()


