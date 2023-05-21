#include "ast_visitor.hpp"

#include <charconv>
#include <moe/rt_check.hpp>
#include <dbg.hpp>

namespace front::helper {

int32_t parse_int_literal(std::string_view str) {
	int32_t num = 0;
	if (str.size() > 2 && str.substr(0, 2) == "0x") {
		auto result = std::from_chars(str.data() + 2, str.data() + str.size(), num, 16);
		moe_assert(result.ec == std::errc(), "Invalid hexadecimal string");
	} else if (str.size() > 1 && str[0] == '0') {
		auto result = std::from_chars(str.data() + 1, str.data() + str.size(), num, 8);
		moe_assert(result.ec == std::errc(), "Invalid octal string");
	} else {
		auto result = std::from_chars(str.data(), str.data() + str.size(), num, 10);
		moe_assert(result.ec == std::errc(), "Invalid decimal string");
	}
	return num;
}
}// namespace front::helper