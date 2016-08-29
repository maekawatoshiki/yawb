#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

struct selector_t {

};
struct decl_t {
};

struct rule_t {
	std::vector<selector_t> selectors;
	std::vector<decl_t> decls;
};

class Stylesheet {
	public:
		std::vector<rule_t> rules;
};
