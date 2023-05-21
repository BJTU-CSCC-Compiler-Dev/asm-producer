#pragma once

#include <memory>

#include <moe/rt_check.hpp>

namespace mir {
class DumpHelper;


class BaseType;

std::unique_ptr<BaseType> dup_type(const std::unique_ptr<BaseType> & type);

class BaseType {
  public:
	virtual ~BaseType() = default;
	[[nodiscard]] virtual std::unique_ptr<BaseType> get_derefed() const = 0;

	virtual std::string dump() = 0;

  protected:
};

class PrimType : public BaseType {
  public:
	enum class Type {
		i32_t,
		float_t,
		bool_t,
		void_t,
	};

	//	constructor
	explicit PrimType(mir::PrimType::Type type) : type_(type) {}

	//	getter
	[[nodiscard]] std::unique_ptr<BaseType> get_derefed() const override { return nullptr; }
	std::string dump() override;

  protected:
	Type type_;
};

std::unique_ptr<PrimType> make_prim_type(PrimType::Type type);

class PointerType : public BaseType {
  public:
	//	constructor
	explicit PointerType(std::unique_ptr<BaseType> pointTo);
	PointerType(const PointerType & pointerType);

	[[nodiscard]] std::unique_ptr<BaseType> get_derefed() const override;
	std::string dump() override;

  protected:
	std::unique_ptr<BaseType> pointTo_;
};

std::unique_ptr<PointerType> make_pointer_type(std::unique_ptr<BaseType> pointTo);

std::unique_ptr<BaseType> make_derefed_type(std::unique_ptr<BaseType> pointer);

}// namespace mir