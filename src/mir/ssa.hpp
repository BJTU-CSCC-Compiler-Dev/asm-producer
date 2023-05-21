#pragma once
#include <cstdint>
#include <memory>
#include <utility>

#include "mir/type.hpp"
#include "mir/usedef.hpp"

namespace mir {

class ConstIntSsa : public User {
  public:
	explicit ConstIntSsa(uint32_t val) : User(make_prim_type(PrimType::Type::i32_t)) {}
	std::string dump(DumpHelper & dh) const override;
	[[nodiscard]] bool is_const() const override;

  protected:
	uint32_t val = 0;
};

class AllocaSsa : public User {
  public:
	explicit AllocaSsa(std::unique_ptr<BaseType> pointTo, std::string name = "");
	std::string dump(DumpHelper & dh) const override;

  protected:
	//	the type of the value allocaed
	std::unique_ptr<BaseType> pointTo_;
};

class StoreSsa : public User {
  public:
	StoreSsa(std::shared_ptr<Value> storeFrom, std::shared_ptr<Value> storeTo);
	std::string dump(DumpHelper & dh) const override;

  protected:
	Use storeFrom_;
	Use storeTo_;
};

class LoadSsa : public User {
  public:
	explicit LoadSsa(const std::shared_ptr<Value> & loadFrom, std::string name = "");
	std::string dump(DumpHelper & dh) const override;

  protected:
	Use loadFrom_;
};

class RetSsa : public User {
  public:
	explicit RetSsa(std::shared_ptr<Value> retVal);

	std::string dump(DumpHelper & dh) const override;
	[[nodiscard]] bool is_terminator() const override;

  protected:
	Use retVal_;
};

class BranchSsa : public User {
  public:
	explicit BranchSsa(std::shared_ptr<Value> cond);
	BranchSsa(std::shared_ptr<Value> cond, const std::shared_ptr<BlockSsa> & trueTarget, const std::shared_ptr<BlockSsa> & falseTarget);

	void set_true_target(const std::shared_ptr<BlockSsa> & target);
	void set_false_target(const std::shared_ptr<BlockSsa> & target);

	[[nodiscard]] bool is_terminator() const override;

  protected:
	Use cond_;
	std::weak_ptr<BlockSsa> trueTarget_, falseTarget_;
};

class JmpSsa : public User {
  public:
	JmpSsa() = default;
	explicit JmpSsa(const std::shared_ptr<BlockSsa> & target);

	void set_target(const std::shared_ptr<BlockSsa> & target);

	[[nodiscard]] bool is_terminator() const override;

	std::string dump(DumpHelper & dh) const override;

  protected:
	std::weak_ptr<BlockSsa> target_;
};

class BlockSsa : public User {
  public:
	BlockSsa() = default;

	explicit BlockSsa(std::string name);
	std::string dump(DumpHelper & dh) const override;

	void add_ssa(std::shared_ptr<User> ssa);

  protected:
	std::vector<Use> insts_;
};

class FuncSsa : public User {
  public:
	FuncSsa() = default;
	FuncSsa(std::unique_ptr<BaseType> retType, std::string name);

	std::string dump(DumpHelper & dh) const override;

	void add_block(std::shared_ptr<BlockSsa> block);

	std::shared_ptr<BlockSsa> new_block(std::string blockName = "");

  protected:
	std::unique_ptr<BaseType> retType_;
	std::list<Use> blocks_;
	std::vector<Use> args_;
};

class CompUnitSsa : public User {
  public:
	CompUnitSsa() = default;

	std::string dump(DumpHelper & dh) const override;
	void add_func(std::shared_ptr<FuncSsa> funcSsa);
	std::shared_ptr<FuncSsa> new_func();

  protected:
	std::vector<Use> funcs_;
};

}// namespace mir