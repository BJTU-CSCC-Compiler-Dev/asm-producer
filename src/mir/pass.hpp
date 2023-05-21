#pragma once

namespace mir {

/*
 *class PassBase {
public:
 virtual ~PassBase() = default;

// return true if is module pass
virtual bool IsModulePass() const = 0;
// run on global values in module, return true if there is modification
virtual bool RunOnModule(UserPtrList &global_vals) = 0;

// return true if is function pass
virtual bool IsFunctionPass() const = 0;
// run on functions, return true if there is modification
virtual bool RunOnFunction(const UserPtr &func) = 0;

// return true if is block pass
virtual bool IsBlockPass() const = 0;
// run on basic blocks, return true if there is modification
virtual bool RunOnBlock(const BlockPtr &block) = 0;

// visitor methods for running on SSA IRs
virtual void RunOn(LoadSSA &ssa) {}
virtual void RunOn(StoreSSA &ssa) {}
virtual void RunOn(AccessSSA &ssa) {}
virtual void RunOn(BinarySSA &ssa) {}
virtual void RunOn(UnarySSA &ssa) {}
virtual void RunOn(CastSSA &ssa) {}
virtual void RunOn(CallSSA &ssa) {}
virtual void RunOn(BranchSSA &ssa) {}
virtual void RunOn(JumpSSA &ssa) {}
virtual void RunOn(ReturnSSA &ssa) {}
virtual void RunOn(FunctionSSA &ssa) {}
virtual void RunOn(GlobalVarSSA &ssa) {}
virtual void RunOn(AllocaSSA &ssa) {}
virtual void RunOn(BlockSSA &ssa) {}
virtual void RunOn(ArgRefSSA &ssa) {}
virtual void RunOn(AsmSSA &ssa) {}
virtual void RunOn(ConstIntSSA &ssa) {}
virtual void RunOn(ConstFloatSSA &ssa) {}
virtual void RunOn(ConstStrSSA &ssa) {}
virtual void RunOn(ConstStructSSA &ssa) {}
virtual void RunOn(ConstArraySSA &ssa) {}
virtual void RunOn(ConstZeroSSA &ssa) {}
};
 */

class Pass {
  protected:
  public:
	virtual ~Pass() = default;
};
}// namespace mir