#include "type.hpp"

#include <moe/rt_check.hpp>

namespace mir {

std::unique_ptr<BaseType> dup_type(const std::unique_ptr<BaseType> & type) {
	auto * p = type.get();
#define dup_if_is(T)                       \
	if (dynamic_cast<T *>(p) != nullptr) { \
		auto * pp = dynamic_cast<T *>(p);  \
		return std::make_unique<T>(*pp);   \
	}

	dup_if_is(PrimType);
	dup_if_is(PointerType);
	moe_panic("dup_type failed.");
#undef dup_if_is
}

std::string PrimType::dump() {
	switch (type_) {
		case Type::i32_t: {
			return "i32";
		}
		case Type::float_t: {
			return "float";
		}
		case Type::bool_t: {
			return "i1";
		}
		case Type::void_t: {
			return "void";
		}
		default: {
			moe_panic("");
		}
	}
}

std::unique_ptr<PrimType> make_prim_type(PrimType::Type type) {
	return std::make_unique<PrimType>(type);
}

//	PointerType
PointerType::PointerType(const PointerType & pointerType) : pointTo_(dup_type(pointerType.pointTo_)) {}
PointerType::PointerType(std::unique_ptr<BaseType> pointTo) : pointTo_(dup_type(pointTo)) {}
std::unique_ptr<BaseType> PointerType::get_derefed() const { return dup_type(pointTo_); }
std::string PointerType::dump() {
	auto s = pointTo_->dump();
	s += "*";
	return s;
}

std::unique_ptr<PointerType> make_pointer_type(std::unique_ptr<BaseType> pointTo) {
	return std::make_unique<PointerType>(std::move(pointTo));
}

std::unique_ptr<BaseType> make_derefed_type(std::unique_ptr<BaseType> pointer) {
	moe_assert(dynamic_cast<PointerType *>(pointer.get()));
	auto p = std::unique_ptr<PointerType>(dynamic_cast<PointerType *>(pointer.release()));
	return p->get_derefed();
}
}// namespace mir
