#pragma once

class IValue
{
public:
	virtual double GetValue() = 0;

	virtual ~IValue() = default;
};