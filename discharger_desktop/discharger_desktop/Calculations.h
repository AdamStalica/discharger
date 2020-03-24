#pragma once
class Calculations
{
	long long elapsedMs_ = 0;
	double voltageSum_ = 0.0;
	double currentSum_ = 0.0;
	int n = 0;

	double getMeanEnergy() {
		return (currentSum_ * voltageSum_) / n;
	}

public:
	void clear() {
		elapsedMs_ = 0;
		voltageSum_ = 0;
		currentSum_ = 0.0;
	}

	void setValues(long long elapsedMs, double current, double volt1, double volt2 = 0.0) {
		elapsedMs_ = elapsedMs;
		currentSum_ += current;
		voltageSum_ += volt1;
		voltageSum_ += volt2;
		++n;
	}

	double computeCapacity() {
		return (getMeanEnergy() * elapsedMs_ / 3600000);
	}

	double computeUsedEnergy() {
		return (currentSum_ * voltageSum_);
	}
};

