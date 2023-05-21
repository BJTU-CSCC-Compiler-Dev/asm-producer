#include "ast_visitor.hpp"

#include <moe/rt_check.hpp>

namespace front {
//	helper func
mir::PrimType::Type to_prim_type(FuncType funcType) {
	switch (funcType) {
		case FuncType::void_t: {
			return mir::PrimType::Type::void_t;
		}
		case FuncType::int_t: {
			return mir::PrimType::Type::i32_t;
		}
		case FuncType::float_t: {
			return mir::PrimType::Type::float_t;
		}
		default: {
			moe_panic("");
		}
	}
}

/**
 * @return std::shared_ptr<CompUnitSsa>
 */
std::any AstVisitor::visitCompUnit(SysYParser::CompUnitContext * context) {
	ctx_.compUnitSsa = std::make_shared<mir::CompUnitSsa>();
	for (auto * p: context->decl()) {
		moe_rt_todo();
	}
	for (auto * p: context->funcDef()) {
		p->accept(this);
	}
	auto p = ctx_.compUnitSsa;
	return p;
}
std::any AstVisitor::visitBType(SysYParser::BTypeContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitLVal(SysYParser::LValContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitRVal(SysYParser::RValContext * context) {
	moe_rt_todo();
}

/**
 * @return std::shared_ptr<Value>
 */
std::any AstVisitor::visitNumber(SysYParser::NumberContext * context) {
	auto p = std::shared_ptr<mir::Value>();
	if (context->IntLiteral()) {
		auto i = helper::parse_int_literal(context->getText());
		p = std::make_shared<mir::ConstIntSsa>(i);
	} else if (context->FloatLiteral()) {
		moe_rt_todo();
	} else {
		moe_panic("");
	}
	return p;
}

std::any AstVisitor::visitFuncRparamList(SysYParser::FuncRparamListContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitExpAsRparam(SysYParser::ExpAsRparamContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitStringAsRparam(SysYParser::StringAsRparamContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitChildren(antlr4::tree::ParseTree * node) {
	std::for_each(node->children.begin(), node->children.end(), [this](auto * p) { p->accept(this); });
	return {};
}

/**
 * @return std::string
 */
std::any AstVisitor::visitTerminal(antlr4::tree::TerminalNode * node) {
	return node->getText();
}

void Ctx::clear() {
	moe_rt_todo();
}
}// namespace front
