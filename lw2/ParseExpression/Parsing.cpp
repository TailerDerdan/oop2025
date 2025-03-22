#include "ParseExpressionModule.h"
#include <stack>



void CalculatePrefixNotation(const std::string& preFixExpression)
{
	std::stack<std::pair<std::string, size_t>> stackForOperations;
	std::stack<size_t> stackForNums;
	size_t posEndOfSequenceOfNumber = 0;

	stackForOperations.push(std::make_pair(preFixExpression.substr(1, 1), posEndOfSequenceOfNumber));
	posEndOfSequenceOfNumber++;

	bool isNegativeNumber = false;
	
	for (char ch : preFixExpression)
	{
		if (ch == '-')
		{
			isNegativeNumber = true;
		}
		if (isdigit(ch))
		{
			std::string numStr(1, ch);
			size_t num = std::stoi(numStr);
			if (isNegativeNumber)
			{
				num *= -1;
			}
		}
		else
		{

		}
	}
}