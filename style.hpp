#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

struct color_t {
	int r, g, b, a;
};
struct value_t {
	std::string keyword;
	int num;
	color_t color;
};
struct selector_t {
	std::string tag_name;
	std::string id;
	std::vector<std::string> class_name;
};
struct decl_t {
	std::string name;
	value_t val;
};

struct rule_t {
	std::vector<selector_t> selectors;
	std::vector<decl_t> decls;
};

class Stylesheet {
	public:
		std::vector<rule_t> rules;
};

struct css_token_t {
	std::string str;
};
class StyleLexer  {
	private:
		std::vector<css_token_t> token;
	public:
		void lexer(std::string);
		std::vector<css_token_t> &get_token() { return token; }
};
class StyleParser {
	private:
		Stylesheet style;
	public:
		selector_t parse_one_selector(std::vector<css_token_t>::iterator &);
		std::vector<selector_t> parse_selector(std::vector<css_token_t>::iterator &);
		decl_t parse_one_decl(std::vector<css_token_t>::iterator &);
		std::vector<decl_t> parse_decl(std::vector<css_token_t>::iterator &);
		rule_t parse_one_rule(std::vector<css_token_t>::iterator &);
		std::vector<rule_t> parse_rule(std::vector<css_token_t>::iterator, std::vector<css_token_t>::iterator);
		void parse(std::vector<css_token_t> &);
};
