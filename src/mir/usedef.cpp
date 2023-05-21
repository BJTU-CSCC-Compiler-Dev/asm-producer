#include "usedef.hpp"

#include <utility>

namespace mir {
User::User(std::unique_ptr<BaseType> type, std::string name) : Value(std::move(type), std::move(name)) {}

//	Value
Value & Value::set_name(std::string name) {
	name_ = std::move(name);
	return *this;
}
const std::string & Value::get_name() const { return name_; }
std::unique_ptr<BaseType> Value::get_type() const {
	return dup_type(type_);
}
bool Value::is_const() const {
	return false;
}

}// namespace mir
