#include "symbol_table.hpp"

#include <moe/rt_check.hpp>

namespace front {

void SymbolTable::new_scope() {
	if (tableStack_.empty()) {
		tableStack_.emplace(std::make_shared<ScopeTable>());
	} else {
		auto newTable = std::make_shared<ScopeTable>(tableStack_.top());
		tableStack_.emplace(std::make_shared<ScopeTable>(tableStack_.top()));
	}
}

std::vector<std::shared_ptr<mir::AllocaSsa>> SymbolTable::pop_scope() {
	moe_assert(!tableStack_.empty());
	auto thisLevel = tableStack_.top()->this_level();
	auto r = std::vector<std::shared_ptr<mir::AllocaSsa>>();
	for (auto & [_, ssa]: thisLevel) {
		r.emplace_back(ssa);
	}
	tableStack_.pop();
	return r;
}

}// namespace front
