#pragma once
#include <iostream>
#include <string>
#include <vector>
class ping {
public:
	int PingResult;
	int FailedCounter;
	bool IsFailed;
	bool WaitingConnect;
	std::vector <std::string> FailedTime = {};
};