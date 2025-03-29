#pragma once

enum class Direction
{
	Forward,
	Backward,
	Standing
};
enum class Gear
{
	ReverseGear = -1,
	NeutralGear,
	FirstGear,
	SecondGear,
	ThirdGear,
	FourthGear,
	FiveGear
};

class Car
{
public:
	Car() = default;

	bool isTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:

	struct SpeedLimits
	{
		int minSpeed = 0;
		int maxSpeed = 0;

		SpeedLimits() = default;

		void SetLimits(int min, int max)
		{
			minSpeed = min;
			maxSpeed = max;
		}
	};

	void ChangeGearDependingSpeed(const SpeedLimits& speedLimits, int gear);
	bool IsItPossibleToChangeSpeed(const SpeedLimits& speedLimits, int speed);

private:
	bool m_engineIsOn = false;
	int m_speed = 0;
	Gear m_gear = Gear::NeutralGear;
};