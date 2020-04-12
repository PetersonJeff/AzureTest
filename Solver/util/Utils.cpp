#include "pch.h"
#include "Utils.h"

#include <windows.h>

#include <sstream>
#include <processthreadsapi.h>

using namespace std;

std::string Utils::trim(const std::string& tmp) {
	int start = 0;
	int end = -1;

	while (start < (int)tmp.size() && isspace(tmp[start])) {
		start++;
	}

	end = tmp.size() - 1;

	while (end > 0 && isspace(tmp[end])) {
		end--;
	}

	if (end < start) {
		return "";
	}

	return tmp.substr(start, (end - start) + 1);
}

std::string Utils::getCurrentThreadId() {
	stringstream s;
#if defined (WIN32) || defined (WIN64)
	s << ::GetCurrentThreadId();
#else
	s.ostrm() << ::pthread_self();
#endif
	return s.str();
}
