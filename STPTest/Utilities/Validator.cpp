#include "Validator.h"
#include "../SimplePopupDialog.h"
#include "../Program.h"

bool Validator::String(CString str, std::string ruleStr)
{
	std::vector<std::string> rules = {};

	std::string currentRule = "";
	for (int i = 0; i < ruleStr.length(); i++)
	{
		if (ruleStr[i] != ',')
		{
			currentRule += ruleStr[i];
			if (i == ruleStr.length() - 1)
			{
				rules.push_back(currentRule);
			}
		}
		else
		{
			rules.push_back(currentRule);
			currentRule.empty();
		}
	}

	for (std::string rule : rules)
	{
		if (rule == "required")
		{
			if (str.GetLength() == 0) return false;
		}
	}

	return true;
}
