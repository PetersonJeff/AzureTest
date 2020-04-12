#pragma once
#include <string>

class SolutionReport
{
public:
	SolutionReport();

	void init();

	bool processReport();

	bool printReport() const;

private:

	std::string _reportName;
};

