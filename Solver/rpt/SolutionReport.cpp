#include "pch.h"
#include "SolutionReport.h"

#include <cstdio>

#include <cfg/CfgManager.h>

using namespace std;

SolutionReport::SolutionReport() {
	_reportName = "solution";
}

void SolutionReport::init() {
	_reportName = CfgStringValue("solution.report.name", _reportName);
}

bool SolutionReport::processReport() {
	//do work

	return true;
}

bool SolutionReport::printReport() const {

	string fileName = _reportName + ".txt";

	FILE* pFile;
	
	pFile = fopen(fileName.c_str(), "w");

	if (pFile != nullptr) {
		fputs("\t\t\t\t\t\t\tSolution Report\n", pFile);

		fputs("report line 1\n", pFile);
		fputs("report line 2\n", pFile);
		fputs("report line 3\n", pFile);
		fputs("report line 4\n", pFile);

		fclose(pFile);
	}
	
	
	return true;
}


