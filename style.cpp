#include "style.hpp"

void StyleLexer::lexer(std::string str) {
	for(auto it = str.begin(); it != str.end(); ++it) {
		if(isdigit(*it) || isalpha(*it)) {
			std::string s;
			while(isalpha(*it) || isdigit(*it) || *it=='_' || *it=='-')
				s += *(it++);
			token.push_back({s});
			--it;
		} else if(!isblank(*it)) {
			std::string s; s += *it;
			token.push_back({s});
		}
	}
	for(auto &t : token) {
		std::cout << "tok:" << t.str << std::endl;
	}
}

selector_t StyleParser::parse_one_selector(std::vector<css_token_t>::iterator &it) {
	selector_t sel;
	if((*it).str == "#") { // id
		it++;
		sel.id = (*it).str;
		it++;
	} else if((*it).str == ".") {
		it++;
		sel.class_name.push_back((*it).str);
		it++;
	} else {
		sel.tag_name = (*it).str;
		it++;
	}
	return sel;
}
std::vector<selector_t> StyleParser::parse_selector(std::vector<css_token_t>::iterator &it) {
	std::vector<selector_t> sels;
	while((*it).str != "{") {
		sels.push_back(parse_one_selector(it));
		if((*it).str == ",") ++it;
	}
	return sels;
}
decl_t StyleParser::parse_one_decl(std::vector<css_token_t>::iterator &it) {
	decl_t decl;
	decl.name = (*it++).str; it++; // :
	decl.val.num = 10;
	return decl;
}
std::vector<decl_t> StyleParser::parse_decl(std::vector<css_token_t>::iterator &it) {
	std::vector<decl_t> decls;
	if((*it).str == "{") {
		it++;
		while((*it).str != "}") {
			decls.push_back(parse_one_decl(it));
			if((*it).str == ";") it++;
		}
		it++;
	}
	return decls;
}
rule_t StyleParser::parse_one_rule(std::vector<css_token_t>::iterator &it) {
	rule_t rule;
	rule.selectors = parse_selector(it);
	rule.decls = parse_decl(it);
	return rule;
}
std::vector<rule_t> StyleParser::parse_rule(std::vector<css_token_t>::iterator it, std::vector<css_token_t>::iterator end) {
	std::vector<rule_t> rules;
	while(it != end) {
		rules.push_back(parse_one_rule(it));
	}
	return rules;
}
void StyleParser::parse(std::vector<css_token_t> &token) {
	style.rules = parse_rule(token.begin(), token.end());
}
