#include "front/ast_visitor.hpp"

#include <moe/rt_check.hpp>
#include <dbg.hpp>

namespace front {
std::any AstVisitor::visitFuncFparamList(SysYParser::FuncFparamListContext * context) {
	moe_rt_todo();
}
std::any AstVisitor::visitFuncFparam(SysYParser::FuncFparamContext * context) {
	moe_rt_todo();
}

/**
 * @return FuncType
 */
std::any AstVisitor::visitFuncType(SysYParser::FuncTypeContext * context) {
	auto s = context->getText();
	if (s == "int") {
		return FuncType::int_t;
	} else if (s == "float") {
		return FuncType::float_t;
	} else if (s == "void") {
		return FuncType::void_t;
	} else {
		moe_panic("Unknown func type.");
	}
}
std::any AstVisitor::visitFuncDef(SysYParser::FuncDefContext * context) {
	ctx_.symbolTable.new_scope();
	auto funcType = std::any_cast<FuncType>(context->funcType()->accept(this));
	auto funcName = std::any_cast<std::string>(context->Identifier()->accept(this));
	if (context->funcFparamList()) {
		moe_rt_todo();
	}
	{//	func info
		auto curFunc = std::make_shared<mir::FuncSsa>(mir::make_prim_type(to_prim_type(funcType)), funcName);
		ctx_.compUnitSsa->add_func(curFunc);
		ctx_.funcSsa = curFunc;
	}
	{//	prepare ret
		ctx_.retVal = std::make_shared<mir::AllocaSsa>(mir::make_prim_type(to_prim_type(funcType)), "retval");
	}
	{//	Exit bb
		auto exitBb = std::make_shared<mir::BlockSsa>("exit");
		auto loadRetVal = std::make_shared<mir::LoadSsa>(ctx_.retVal);
		auto retSsa = std::make_shared<mir::RetSsa>(loadRetVal);
		exitBb->add_ssa(loadRetVal);
		exitBb->add_ssa(retSsa);
		ctx_.exitBb = exitBb;
	}
	auto rInfo = std::any_cast<StmtRinfo>(context->block()->accept(this));
	{//	Entry bb
		ctx_.entryBb = std::make_shared<mir::BlockSsa>("entry");
		auto l = ctx_.symbolTable.pop_scope();
		for (auto x: l) ctx_.entryBb->add_ssa(std::move(x));
		ctx_.entryBb->add_ssa(ctx_.retVal);
	}
	{//	main block
		if (rInfo.is_alpha()) {
			moe_rt_todo();
		} else if (rInfo.is_beta()) {
			moe_rt_todo();
		} else if (rInfo.is_theta()) {
			auto bb = std::make_shared<mir::BlockSsa>("main");
			auto theta = rInfo.theta();
			for (auto ssa: theta.list) {
				bb->add_ssa(std::move(ssa));
			}
			ctx_.entryBb->add_ssa(std::make_shared<mir::JmpSsa>(bb));
			theta.jmpSsa->set_target(ctx_.exitBb);
			//	combine all
			ctx_.funcSsa->add_block(ctx_.entryBb);
			ctx_.funcSsa->add_block(bb);
			ctx_.funcSsa->add_block(ctx_.exitBb);
		} else {
			moe_panic("");
		}
	}
	return {};
}
}// namespace front