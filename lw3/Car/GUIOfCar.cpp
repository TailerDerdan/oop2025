#include "GUIOfCar.h"
#include <string>

GUIOfCar::GUIOfCar(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap(
		  { "SetGear", [] }){};

void GUIOfCar::OutputGear()
{
	switch (m_car.GetGear())
	{
	case Gear::ReverseGear:
		m_output << "Gear is reverse" << std::endl;
		break;
	case Gear::NeutralGear:
		m_output << "Gear is neutral" << std::endl;
		break;
	case Gear::FirstGear:
		m_output << "Gear is first" << std::endl;
		break;
	case Gear::SecondGear:
		m_output << "Gear is second" << std::endl;
		break;
	case Gear::ThirdGear:
		m_output << "Gear is third" << std::endl;
		break;
	case Gear::FourthGear:
		m_output << "Gear is fourth" << std::endl;
		break;
	case Gear::FiveGear:
		m_output << "Gear is fifth" << std::endl;
		break;
	default:
		break;
	}
}

void GUIOfCar::OutputStateEngine()
{
	if (m_car.isTurnedOn())
	{
		m_output << "Engine is on" << std::endl;
	}
	if (!m_car.isTurnedOn())
	{
		m_output << "Engine is off" << std::endl;
	}
}

void GUIOfCar::OutputDirection()
{
	switch (m_car.GetDirection())
	{
	case Direction::Backward:
		m_output << "Direction is backward" << std::endl;
		break;
	case Direction::Forward:
		m_output << "Direction is forward" << std::endl;
		break;
	case Direction::Standing:
		m_output << "Direction is standing" << std::endl;
		break;
	default:
		break;
	}
}

void GUIOfCar::Info()
{
	OutputGear();
	m_output << "Speed is " << m_car.GetSpeed() << std::endl;
	OutputStateEngine();
	OutputDirection();
}

bool GUIOfCar::HandleCommandWithParams(const std::string& line)
{
	std::string command;
	std::string argument;
	size_t posSpace = line.find_first_of(" ");

	if (posSpace <= line.size())
	{
		command.append(line, 0, posSpace);
		argument.append(line, posSpace + 1, line.size() - posSpace);

		if (command == "SetGear")
		{
			if (!m_car.SetGear(stoi(argument)))
			{
				m_output << "You can't change gear to " << argument << std::endl;
			}
			return true;
		}
		if (command == "SetSpeed")
		{
			if (!m_car.SetSpeed(stoi(argument)))
			{
				m_output << "You can't drive at " << argument << " this speed" << std::endl;
			}
			return true;
		}
	}
	return false;
}

// сделать через map with functions
void GUIOfCar::DialogWithUser()
{
	Car m_car;
	std::string line;

	while (std::getline(std::cin, line))
	{
		if (line == "Info")
		{
			Info();
			continue;
		}
		if (line == "EngineOn")
		{
			m_car.TurnOnEngine();
			continue;
		}
		if (line == "EngineOff")
		{
			if (!m_car.TurnOffEngine())
			{
				m_output << "You can't turn off the engine" << std::endl;
			}
			continue;
		}

		if (HandleCommandWithParams(line))
		{
			continue;
		}

		m_output << "Unknow kommand" << std::endl;
	}
}