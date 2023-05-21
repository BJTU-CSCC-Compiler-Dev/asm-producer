#include "front/ast_visitor.hpp"

#include <moe/rt_check.hpp>

namespace front {
/**
 * @return ExpRinfo
 */
std::any AstVisitor::visitAddToMulExp(SysYParser::AddToMulExpContext * context) {
	return context->mulExp()->accept(this);
}

/**
 * @return ExpRinfo
 */
std::any AstVisitor::visitAddTwoExp(SysYParser::AddTwoExpContext * context) {
	moe_rt_todo();
}

/**
 * @return ExpRinfo
 */
std::any AstVisitor::visitMulToUnaryExp(SysYParser::MulToUnaryExpContext * context) {
	return context->unaryExp()->accept(this);
}

/**
 * @return ExpRinfo
 */
std::any AstVisitor::visitMulTwoExp(SysYParser::MulTwoExpContext * context) {
	moe_rt_todo();
}

/**
 * @return ExpRinfo
 */
std::any AstVisitor::visitUnaryToPrimExp(SysYParser::UnaryToPrimExpContext * context) {
	return context->primExp()->accept(this);
}

/**
 * @return ExpRinfo
 */
std::any AstVisitor::visitPrimParenExp(SysYParser::PrimParenExpContext * context) {
	return context->exp()->accept(this);
}

/**
 * @return ExpRinfo
 */
std::any AstVisitor::visitPrimRvalExp(SysYParser::PrimRvalExpContext * context) {
	moe_rt_todo();
}

/**
 * @return ExpRinfo
 */
std::any AstVisitor::visitPrimConstExp(SysYParser::PrimConstExpContext * context) {
	auto r = ExpRinfo{};
	auto v = std::any_cast<std::shared_ptr<mir::Value>>(context->number()->accept(this));
	r.value = v;
	return r;
}

std::any AstVisitor::visitUnaryFuncCallExp(SysYParser::UnaryFuncCallExpContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitUnaryOpExp(SysYParser::UnaryOpExpContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitUnaryOp(SysYParser::UnaryOpContext * context) {
	moe_rt_todo();
}

std::any AstVisitor::visitRelToAddExp(SysYParser::RelToAddExpContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitRelTwoExp(SysYParser::RelTwoExpContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitEqTwoExp(SysYParser::EqTwoExpContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitEqToRelExp(SysYParser::EqToRelExpContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitLAndToEqExp(SysYParser::LAndToEqExpContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitLAndTwoExp(SysYParser::LAndTwoExpContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitLOrToLandExp(SysYParser::LOrToLandExpContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitLOrTwoExp(SysYParser::LOrTwoExpContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitConstExp(SysYParser::ConstExpContext * context) {
	moe_rt_todo();
}
/**
 * @return ExpRinfo
 */
std::any AstVisitor::visitExp(SysYParser::ExpContext * context) {
	return context->addExp()->accept(this);
}

}// namespace front