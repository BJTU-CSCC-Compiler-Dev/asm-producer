#include "ssa.hpp"
#include "usedef.hpp"


#include <utility>
#include <moe/rt_check.hpp>
#include <dbg.hpp>

namespace mir {
//	ConstIntSsa
std::string ConstIntSsa::dump(mir::DumpHelper & dh) const {
	return std::to_string(val);
}
bool ConstIntSsa::is_const() const {
	return true;
}

//	FuncSsa
FuncSsa::FuncSsa(std::unique_ptr<BaseType> retType, std::string name)
	: User(nullptr, std::move(name)), retType_(std::move(retType)), blocks_(), args_() {}
std::string FuncSsa::dump(DumpHelper & dh) const {
	auto s = std::string();
	moe_rt_warning("FuncSsa Todo: formal args.");
	s += dh.concat("define", "dso_local", retType_->dump(), dh.name_of_func(name_), "(", ")", "{");
	for (const auto & bb: blocks_) {
		s += bb.value()->dump(dh);
	}
	s += "}";
	return s;
}
void FuncSsa::add_block(std::shared_ptr<BlockSsa> block) {
	blocks_.emplace_back(std::move(block), this);
}
std::shared_ptr<BlockSsa> FuncSsa::new_block(std::string blockName) {
	auto p = std::make_shared<BlockSsa>(std::move(blockName));
	blocks_.emplace_back(p, this);
	return p;
}

//	CompUnitSsa
std::string CompUnitSsa::dump(DumpHelper & dh) const {
	auto s = std::string();
	for (const auto & func: funcs_) {
		s += func.value()->dump(dh);
	}
	return s;
}
void CompUnitSsa::add_func(std::shared_ptr<FuncSsa> funcSsa) {
	funcs_.emplace_back(std::move(funcSsa), this);
}
std::shared_ptr<FuncSsa> CompUnitSsa::new_func() {
	auto p = std::make_shared<FuncSsa>();
	funcs_.emplace_back(p, this);
	return p;
}

//	StoreSsa
StoreSsa::StoreSsa(std::shared_ptr<Value> storeFrom, std::shared_ptr<Value> storeTo)
	: User(), storeFrom_(std::move(storeFrom), this), storeTo_(std::move(storeTo), this) {
	moe_rt_warning("Need a function to check the type of two Use.");
}
std::string StoreSsa::dump(DumpHelper & dh) const {
	auto s = std::string();
	s += dh.tab_concat("store", storeFrom_.value()->get_type()->dump(), dh.value(storeFrom_.value().get()), ",",
					   storeTo_.value()->get_type()->dump(), dh.value(storeTo_.value().get()));
	return s;
}

//	RetSsa
RetSsa::RetSsa(std::shared_ptr<Value> retVal) : User(), retVal_(std::move(retVal), this) {}
bool RetSsa::is_terminator() const {
	return true;
}
std::string RetSsa::dump(DumpHelper & dh) const {
	auto s = std::string();
	s += dh.tab_concat("ret", retVal_.value()->get_type()->dump(), dh.value(retVal_.value().get()));
	return s;
}

//	AllocaSsa
AllocaSsa::AllocaSsa(std::unique_ptr<BaseType> pointTo, std::string name)
	: User(make_pointer_type(dup_type(pointTo)), std::move(name)), pointTo_(std::move(pointTo)) {}
std::string AllocaSsa::dump(DumpHelper & dh) const {
	auto s = std::string();
	s += dh.tab_concat(dh.value(this), "=", "alloca", pointTo_->dump());
	return s;
}

//	BranchSsa
BranchSsa::BranchSsa(std::shared_ptr<Value> cond) : User(), cond_(std::move(cond), this) {}
BranchSsa::BranchSsa(std::shared_ptr<Value> cond, const std::shared_ptr<BlockSsa> & trueTarget, const std::shared_ptr<BlockSsa> & falseTarget)
	: User(), cond_(std::move(cond), this), trueTarget_(trueTarget), falseTarget_(falseTarget) {}
void BranchSsa::set_true_target(const std::shared_ptr<BlockSsa> & target) {
	trueTarget_ = target;
}
void BranchSsa::set_false_target(const std::shared_ptr<BlockSsa> & target) {
	falseTarget_ = target;
}
bool BranchSsa::is_terminator() const {
	return true;
}

//	JmpSsa
JmpSsa::JmpSsa(const std::shared_ptr<BlockSsa> & target) : User(), target_(target) {}
void JmpSsa::set_target(const std::shared_ptr<BlockSsa> & target) {
	target_ = target;
}
bool JmpSsa::is_terminator() const {
	return true;
}
std::string JmpSsa::dump(DumpHelper & dh) const {
	auto s = std::string();
	s += dh.tab_concat("br", "label", dh.label(*target_.lock()));
	return s;
}

//	BlockSsa
BlockSsa::BlockSsa(std::string name) : User(nullptr, std::move(name)) {}
void BlockSsa::add_ssa(std::shared_ptr<User> ssa) {
	insts_.emplace_back(std::move(ssa), this);
}
std::string BlockSsa::dump(DumpHelper & dh) const {
	auto s = std::string();
	s += dh.concat(dh.label(*this, false), ":");
	for (const auto & ssa: insts_) {
		s += ssa.value()->dump(dh);
	}
	return s;
}


std::string DumpHelper::label(const BlockSsa & blockSsa, bool withHead) {
	auto s = std::string(({
		withHead ? "%" : "";
	}));
	return s + "l_label_" + blockSsa.get_name() + "_" + get_id_str(&blockSsa);
}
std::string DumpHelper::value(const Value * p, bool withHead) {
	moe_rt_warning("Add judgement to const and non-const value");
	if (p->is_const()) {
		return p->dump(*this);
	} else {
		auto s = std::string(({
			withHead ? "%" : "";
		}));
		return s + "l_val_" + p->get_name() + "_" + get_id_str(p);
	}
}
LoadSsa::LoadSsa(const std::shared_ptr<Value> & loadFrom, std::string name)
	: User(make_derefed_type(dup_type(loadFrom->get_type())), std::move(name)), loadFrom_(loadFrom, this) {
}
std::string LoadSsa::dump(DumpHelper & dh) const {
	auto s = std::string();
	s += dh.tab_concat(dh.value(this), "=", "load", type_->dump(), ",",
					   loadFrom_.value()->get_type()->dump(), dh.value(loadFrom_.value().get()));
	return s;
}
}// namespace mir
