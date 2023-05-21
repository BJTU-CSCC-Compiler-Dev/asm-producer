#include "front/ast_visitor.hpp"

#include <moe/rt_check.hpp>
#include <dbg.hpp>

namespace front {
/**
 * @return StmtRinfo
 */
std::any AstVisitor::visitBlockItem(SysYParser::BlockItemContext * context) {
	if (context->stmt()) {
		return context->stmt()->accept(this);
	} else if (context->decl()) {
		moe_rt_todo();
		//	Just return AlphaStmtRinfo
		return context->decl()->accept(this);
	} else {
		moe_panic("");
	}
}

/**
 * @return StmtRinfo
 */
std::any AstVisitor::visitBlock(SysYParser::BlockContext * context) {
	auto r = StmtRinfo{.info = AlphaStmtRinfo()};
	for (auto * p: context->blockItem()) {
		if (p->decl()) {
			//	block item is decl
			moe_rt_todo();
		} else if (p->stmt()) {
			//	block item is stmt
			auto nr = std::any_cast<StmtRinfo>(p->stmt()->accept(this));
			if (nr.is_alpha()) {
				moe_rt_todo();
			} else if (nr.is_beta()) {
				moe_rt_todo();
			} else if (nr.is_theta()) {
				auto nrTheta = nr.theta();
				if (r.is_alpha()) {
					auto rAlpha = r.alpha();
					rAlpha.list.splice(rAlpha.list.end(), nrTheta.list);
					r = StmtRinfo{.info = ThetaStmtRinfo{.list = rAlpha.list, .jmpSsa = nrTheta.jmpSsa}};
//					dbg(r.theta().list.size());
				} else if (r.is_beta()) {
					moe_rt_todo();
				} else if (r.is_theta()) {
					moe_rt_todo();
				} else {
					moe_panic("");
				}
			}
		} else {
			moe_panic("");
		}
	}
	return r;
}

std::any AstVisitor::visitAssignmentStmt(SysYParser::AssignmentStmtContext * context) {
	moe_rt_todo();
}

std::any AstVisitor::visitExpStmt(SysYParser::ExpStmtContext * context) {
	moe_rt_todo();
}

std::any AstVisitor::visitBlockStmt(SysYParser::BlockStmtContext * context) {
	moe_rt_todo();
}

std::any AstVisitor::visitIfStmt(SysYParser::IfStmtContext * context) {
	moe_rt_todo();
}

std::any AstVisitor::visitIfElseStmt(SysYParser::IfElseStmtContext * context) {
	moe_rt_todo();
}

std::any AstVisitor::visitWhileStmt(SysYParser::WhileStmtContext * context) {
	moe_rt_todo();
}

std::any AstVisitor::visitBreakStmt(SysYParser::BreakStmtContext * context) {
	moe_rt_todo();
}

std::any AstVisitor::visitContinueStmt(SysYParser::ContinueStmtContext * context) {
	moe_rt_todo();
}

/***
 * @return StmtRinfo
 */
std::any AstVisitor::visitReturnStmt(SysYParser::ReturnStmtContext * context) {
	if (context->exp()) {
		auto expRinfo = std::any_cast<ExpRinfo>(context->exp()->accept(this));
		auto storeRetSsa = std::make_shared<mir::StoreSsa>(expRinfo.value, ctx_.retVal);
		auto jmpToExit = std::make_shared<mir::JmpSsa>();
		expRinfo.ssaList.emplace_back(storeRetSsa);
		expRinfo.ssaList.emplace_back(jmpToExit);
		auto stmtRinfo = StmtRinfo{.info = ThetaStmtRinfo{.list = expRinfo.ssaList, .jmpSsa = jmpToExit}};
		return stmtRinfo;
	} else {
		moe_rt_todo();
	}
}

std::any AstVisitor::visitCond(SysYParser::CondContext * context) {
	moe_rt_todo();
}

}// namespace front