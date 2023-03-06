#include "EmployeesDialog.h"
#include "Program.h"
#include "EmployeeDialog.h"
#include "Utilities/Validator.h"
#include "SimplePopupDialog.h"

EmployeesDialog::EmployeesDialog(CWnd* parentWnd) : CDialogExt(IDD),
employees()
{
	Create(IDD, parentWnd);
}

EmployeesDialog::~EmployeesDialog()
{
}

void EmployeesDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EMPLOYEES_LIST, ctrlEmployees);
}

BOOL EmployeesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Setup the list
    ListView_SetExtendedListViewStyle(ctrlEmployees, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    ctrlEmployees.InsertColumn(0, L"ID", LVCFMT_LEFT, -1, 0);
    ctrlEmployees.InsertColumn(1, L"First name", LVCFMT_LEFT, -1, 1);
    ctrlEmployees.InsertColumn(2, L"Last name", LVCFMT_LEFT, -1, 2);
    ctrlEmployees.InsertColumn(3, L"Starting date", LVCFMT_LEFT, -1, 3);
    ctrlEmployees.InsertColumn(4, L"Vacation days", LVCFMT_LEFT, -1, 4);
    ctrlEmployees.InsertColumn(5, L"Position", LVCFMT_LEFT, -1, 5);
    ctrlEmployees.InsertColumn(6, L"Office", LVCFMT_LEFT, -1, 6);
    ctrlEmployees.InsertColumn(7, L"Assigned head", LVCFMT_LEFT, -1, 7);

    LoadEmployees();

    ResizeToParent();

    return TRUE;
}

void EmployeesDialog::LoadEmployees()
{
    ctrlEmployees.DeleteAllItems();

    CString query(
        "SELECT * FROM employees"
    );
    Employee::Read(employees, query);
    Employee::LoadOffice(employees);
    Employee::LoadHeadChief(employees);

    for (int i = 0; i < employees.GetSize(); ++i)
    {
        ctrlEmployees.InsertItem(i, employees[i].id, 0);
        ctrlEmployees.SetItemText(i, 1, employees[i].firstName);
        ctrlEmployees.SetItemText(i, 2, employees[i].lastName);
        ctrlEmployees.SetItemText(i, 3, employees[i].startingDate);
        ctrlEmployees.SetItemText(i, 4, employees[i].vacationDays);
        ctrlEmployees.SetItemText(i, 5, Employee::PosIntToStr(StrToInt(employees[i].position)));
        ctrlEmployees.SetItemText(i, 6, employees[i].office ? employees[i].office->GetDescriptiveStr() : L"");
        ctrlEmployees.SetItemText(i, 7, employees[i].headChief ? employees[i].headChief->GetDescriptiveStr() : L"");
    }
}

void EmployeesDialog::OnOK()
{
}

void EmployeesDialog::ResizeToParent()
{
    CDialogExt::ResizeToParent();
    OptimizeColumnWidths();
}

void EmployeesDialog::OptimizeColumnWidths()
{
    CRect rect;
    ctrlEmployees.GetWindowRect(&rect);
    for (int i = 0; i < ctrlEmployees.GetHeaderCtrl()->GetItemCount(); ++i)
    {
        ctrlEmployees.SetColumnWidth(i, (int)floor(rect.Width() * 0.125f) - 1);
    }
}

void EmployeesDialog::OnBnClickedCreateEmployee()
{
    EmployeeDialog modal(nullptr);
    modal.DoModal();

    LoadEmployees();
}

void EmployeesDialog::OnBnClickedEditEmployee()
{
    int selection = ctrlEmployees.GetSelectionMark();
    if (selection < 0)
    {
        DISPLAY_VAL_ERR(L"You must select an item from the list")
            return;
    }
    EmployeeDialog modal(&employees[selection]);
    modal.DoModal();

    LoadEmployees();
}

void EmployeesDialog::OnBnClickedDeleteEmployee()
{
    int selection = ctrlEmployees.GetSelectionMark();
    if (selection < 0)
    {
        DISPLAY_VAL_ERR(L"You must select an item from the list")
            return;
    }
    Employee::Delete(&employees[selection]);
    LoadEmployees();
}

void EmployeesDialog::OnBnClickedCompanies()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToCompaniesView();
}

void EmployeesDialog::OnBnClickedOffices()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToOfficesView();
}

void EmployeesDialog::OnBnClickedEmployees()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToEmployeesView();
}

BEGIN_MESSAGE_MAP(EmployeesDialog, CDialog)
    ON_BN_CLICKED(IDC_CREATE_EMPLOYEE, &EmployeesDialog::OnBnClickedCreateEmployee)
    ON_BN_CLICKED(IDC_EDIT_EMPLOYEE, &EmployeesDialog::OnBnClickedEditEmployee)
    ON_BN_CLICKED(IDC_DEL_EMPLOYEE, &EmployeesDialog::OnBnClickedDeleteEmployee)
    ON_BN_CLICKED(IDC_COMPANIES, &EmployeesDialog::OnBnClickedCompanies)
    ON_BN_CLICKED(IDC_OFFICES, &EmployeesDialog::OnBnClickedOffices)
    ON_BN_CLICKED(IDC_EMPLOYEES, &EmployeesDialog::OnBnClickedEmployees)
END_MESSAGE_MAP()
