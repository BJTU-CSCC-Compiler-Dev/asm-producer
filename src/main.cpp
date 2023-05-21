#include <iostream>
#include <antlr4-runtime.h>
#include <SysYLexer.h>
#include <SysYParser.h>

#include "config.hpp"
#include "front/ast_visitor.hpp"


int main(int argc, char ** argv) {
	config::init(argc, argv);
	std::cout << config::get() << std::endl;

	//	frontend : source code => ast
	auto sysySrc = std::ifstream();
	sysySrc.open(config::get().sysySrcFilePath);
	antlr4::ANTLRInputStream input(sysySrc);
	front::SysYLexer sysyLexer(&input);
	antlr4::CommonTokenStream tokens(&sysyLexer);
	front::SysYParser sysyParser(&tokens);
	sysyParser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());
	front::SysYParser::CompUnitContext * root = sysyParser.compUnit();

	//	frontend : ast => ir
	auto astVisitor = front::AstVisitor();
	auto r = std::any_cast<std::shared_ptr<mir::CompUnitSsa>>(root->accept(&astVisitor));
	auto dh = mir::DumpHelper();
	std::cout << r->dump(dh) << std::endl;

	return 0;
}