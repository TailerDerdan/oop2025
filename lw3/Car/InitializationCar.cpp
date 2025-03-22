#include "Car.h"
#include <iostream>
#include <map>

const int MIN_SPEED_REVERSE = 0;
const int MAX_SPEED_REVERSE = 20;

const int MIN_SPEED_1 = 0;
const int MAX_SPEED_1 = 30;

const int MIN_SPEED_2 = 20;
const int MAX_SPEED_2 = 50;

const int MIN_SPEED_3 = 30;
const int MAX_SPEED_3 = 60;

const int MIN_SPEED_4 = 40;
const int MAX_SPEED_4 = 90;

const int MIN_SPEED_5 = 50;
const int MAX_SPEED_5 = 150;

const std::map<int, std::pair<int, int>> SPEED_LIMITS = {
	{ -1, std::make_pair(MIN_SPEED_REVERSE, MAX_SPEED_REVERSE) },
	{ 1, std::make_pair(MIN_SPEED_1, MAX_SPEED_1) },
	{ 2, std::make_pair(MIN_SPEED_2, MAX_SPEED_2) },
	{ 3, std::make_pair(MIN_SPEED_3, MAX_SPEED_3) },
	{ 4, std::make_pair(MIN_SPEED_4, MAX_SPEED_4) },
	{ 5, std::make_pair(MIN_SPEED_5, MAX_SPEED_5) }
};

void Car::ChangeGearDependingSpeed(const SpeedLimits& speedLimits, int gear)
{
	if (gear == 0)
	{
		m_gear = Gear::NeutralGear;
		return;
	}
	if (gear == -1)
	{
		if (m_speed == 0)
		{
			m_gear = Gear::ReverseGear;
			return;
		}
	}
	if (m_speed >= speedLimits.minSpeed && m_speed <= speedLimits.maxSpeed)
	{
		m_gear = static_cast<Gear>(gear);
	}
}

bool Car::IsItPossibleToChangeSpeed(const SpeedLimits& speedLimits, int speed)
{
	if (m_gear == Gear::NeutralGear)
	{
		if (speed <= std::abs(speedLimits.maxSpeed))
		{
			if (m_speed < 0)
			{
				m_speed = -speed;
			}
			else
			{
				m_speed = speed;
			}
			return true;
		}
		return false;
	}
	if (speed >= speedLimits.minSpeed && speed <= speedLimits.maxSpeed)
	{
		m_speed = speed;
		if (m_gear == Gear::ReverseGear)
		{
			m_speed = -speed;
		}
		return true;
	}
	return false;
}

bool Car::isTurnedOn() const
{
	return m_engineIsOn;
}

Direction Car::GetDirection() const
{
	if (m_speed > 0)
	{
		return Direction::Forward;
	}
	if (m_speed < 0)
	{
		return Direction::Backward;
	}
	return Direction::Standing;
}

int Car::GetSpeed() const
{
	return std::abs(m_speed);
}

Gear Car::GetGear() const
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	if (!isTurnedOn())
	{
		m_engineIsOn = true;
		m_gear = Gear::NeutralGear;
		m_speed = 0;
	}
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_gear == Gear::NeutralGear && m_speed == 0)
	{
		m_engineIsOn = false;
		return true;
	}
	return false;
}

bool Car::SetGear(int gear)
{
	if (gear < -1 || gear > 5)
	{
		return false;
	}

	if (!m_engineIsOn)
	{
		if (gear == 0)
		{
			m_gear = Gear::NeutralGear;
			return true;
		}
		return false;
	}

	SpeedLimits speedLimits;
	if (gear != 0)
	{
		speedLimits.SetLimits(SPEED_LIMITS.at(int(gear)).first, SPEED_LIMITS.at(int(gear)).second);
	}
	ChangeGearDependingSpeed(speedLimits, gear);

	if (int(m_gear) != gear)
	{
		return false;
	}

	return true;
}

// переделать на map
bool Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		return false;
	}

	SpeedLimits speedLimits;
	if (m_gear == Gear::NeutralGear)
	{
		speedLimits.SetLimits(0, m_speed);
	}
	else
	{
		speedLimits.SetLimits(SPEED_LIMITS.at(int(m_gear)).first, SPEED_LIMITS.at(int(m_gear)).second);
	}

	if (!IsItPossibleToChangeSpeed(speedLimits, speed))
	{
		return false;
	}
	return true;
}