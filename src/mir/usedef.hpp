#pragma once
#include <list>
#include <memory>
#include <map>
#include <utility>
#include <vector>
#include <set>
#include <string>

#include "mir/type.hpp"


namespace mir {

//	predefine
class Value;
class Use;
class User;
class BlockSsa;

class DumpHelper {
	/*
	 * True name format(except function): [gl]_<type>_<name>_<id>
	 */
  public:
	template<typename... T>
	std::string tab_concat(T... ts) {
		auto s = std::string("\t");
		((s += ts, s += " "), ...);
		s += "\n";
		return s;
	}

	template<typename... T>
	std::string concat(T... ts) {
		auto s = std::string();
		((s += ts, s += " "), ...);
		s += "\n";
		return s;
	}

	std::string name_of_func(std::string name) {
		return name;
	}

	std::string label(const BlockSsa & blockSsa, bool withHead = true);

	std::string value(const Value * p, bool withHead = true);

  protected:
	uint32_t id_ = 0;
	std::map<const Value *, uint32_t> idMap_;

	std::string get_id_str(const Value * p) {
		if (!idMap_.count(p)) {
			idMap_[p] = ++id_;
		}
		return std::to_string(idMap_[p]);
	}
};

class Value {
  public:
	Value(std::unique_ptr<BaseType> type, std::string name) : type_(std::move(type)), name_(std::move(name)) {}
	virtual std::string dump(DumpHelper & dh) const = 0;
	bool add_use(Use * use) {
		if (uses_.count(use)) {
			return false;
		} else {
			uses_.insert(use);
			return true;
		}
	}
	bool remove_use(Use * use) {
		if (uses_.count(use)) {
			uses_.erase(use);
			return true;
		} else {
			return false;
		}
	}
	virtual ~Value() = default;

	Value & set_name(std::string name);
	[[nodiscard]] const std::string & get_name() const;

	[[nodiscard]] std::unique_ptr<BaseType> get_type() const;

	virtual bool is_const() const;

  protected:
	std::set<Use *> uses_;
	std::unique_ptr<BaseType> type_;
	std::string name_;
};

class Use {
  public:
	Use(std::shared_ptr<Value> value, User * user) : value_(std::move(value)), user_(user) {}
	Use(const Use & use) : value_(use.value_), user_(use.user_) {
		if (value_) value_->add_use(this);
	}
	Use(Use && use) noexcept : value_(std::move(use.value_)), user_(use.user_) {
		if (value_) {
			value_->remove_use(&use);
			value_->add_use(this);
		}
	}
	Use & operator=(const Use & use) {
		if (this != &use) {
			if (value_) value_->remove_use(this);
			value_ = use.value_;
			if (value_) value_->add_use(this);
			user_ = use.user_;
		}
		return *this;
	}
	Use & operator=(Use && use) noexcept {
		if (this != &use) {
			if (value_) value_->remove_use(this);
			if (use.value_) use.value_->remove_use(&use);
			value_ = std::move(use.value_);
			if (value_) value_->add_use(this);
			user_ = use.user_;
		}
		return *this;
	}
	~Use() {
		if (value_) value_->remove_use(this);
	}

	[[nodiscard]] std::shared_ptr<Value> value() const { return value_; }
	[[nodiscard]] User * user() const { return user_; }

  protected:
	std::shared_ptr<Value> value_;
	User * user_;
};

class User : public Value {
  public:
	explicit User(std::unique_ptr<BaseType> type = nullptr, std::string name = "");
	[[nodiscard]] virtual bool is_terminator() const { return false; }

  protected:
};
}// namespace mir