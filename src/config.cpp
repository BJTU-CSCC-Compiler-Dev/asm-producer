#include "config.hpp"

#include <memory>
#include <argparse.hpp>

namespace config {

std::unique_ptr<Config> up;
Config & init(int argc, char ** argv) {
	up = std::make_unique<Config>();
	auto argParser = argparse::ArgumentParser("AsmProducer");
	argParser.add_argument("sysySrcFilePath")
		.help("SysY source file path.")
		.required();
	argParser.add_argument("-o")
		.help("Dest file path.")
		.required();

	try {
		argParser.parse_args(argc, argv);
		up->sysySrcFilePath = argParser.get("sysySrcFilePath");
		up->dstFilePath = argParser.get("-o");
	} catch (const std::runtime_error & err) {
		std::cerr << err.what() << std::endl;
		std::cerr << argParser << std::endl;
		std::exit(1);
	}
	return *up;
}
Config & get() {
	return *up;
}
}// namespace config
