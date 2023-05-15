#pragma once

#include <iostream>
#include <string>
#include <optional>

namespace config {
struct Config {
	std::string sysySrcFilePath;
	std::string dstFilePath;
	friend std::ostream & operator<<(std::ostream & os, const Config & c) {
		os << "config : {" << std::endl;
		os << "\tsysySrcFilePath = " << c.sysySrcFilePath << std::endl;
		os << "\tdstFilePath     = " << c.dstFilePath << std::endl;
		os << "}" << std::endl;
		return os;
	}
};
Config & init(int argc, char ** argv);
Config & get();
}// namespace config
