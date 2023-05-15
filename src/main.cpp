#include <iostream>
#include <antlr4-runtime.h>
#include <SysYLexer.h>
#include <SysYParser.h>
#include <dbg.hpp>

#include "config.hpp"


int main(int argc, char ** argv) {
	config::init(argc, argv);
	std::cout << config::get() << std::endl;

	auto sysySrc = std::ifstream();
	sysySrc.open(config::get().sysySrcFilePath);
	antlr4::ANTLRInputStream input(sysySrc);
	front::SysYLexer sysyLexer(&input);
	antlr4::CommonTokenStream tokens(&sysyLexer);
	front::SysYParser sysyParser(&tokens);
	sysyParser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());
	front::SysYParser::CompUnitContext * root = sysyParser.compUnit();
	dbg(root->getText());

	return 0;
}