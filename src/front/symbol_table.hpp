#pragma once

#include <map>
#include <stack>
#include <moe/nested_map.hpp>
#include "mir/ssa.hpp"

namespace front {

class SymbolTable {
  public:
	void new_scope();

	std::vector<std::shared_ptr<mir::AllocaSsa>> pop_scope();

  protected:
	using ScopeTable = moe::NestedMap<std::string, std::shared_ptr<mir::AllocaSsa>>;
	std::stack<std::shared_ptr<ScopeTable>> tableStack_;
};
}// namespace front