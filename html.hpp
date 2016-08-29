#pragma once 
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "style.hpp"

enum {
	TAG_HTML,
	TAG_BODY,
	TAG_H,
	TAG_STRING,
};
struct point_t { int x, y; };
struct rect_t {
	point_t top;
	point_t size;
};
class TagInfo {
	public:
		rect_t rect;
};
class TagBase {
	public:
		TagBase() { }
		virtual std::string get_tag_name() = 0;
		virtual TagInfo *get_info() = 0;
		virtual void set_info(TagInfo) = 0;
};
typedef std::vector<TagBase *> vec_tag;
class TagGENERAL : public TagBase {
	public:
		TagGENERAL(std::string _name, vec_tag _content):tag_name(_name), content(_content) { }
		virtual std::string get_tag_name() { return tag_name; }
		virtual TagInfo *get_info() { return &info; }
		virtual void set_info(TagInfo ti) { info = ti; };
		vec_tag content;
		std::string tag_name;
		TagInfo info = {};
};
class TagSTRING : public TagBase {
	public:
		TagSTRING(std::string _content):content(_content) { }
		virtual std::string get_tag_name() { return "string"; }
		virtual TagInfo *get_info() { return &info; }
		virtual void set_info(TagInfo ti) { info = ti; };
		std::string content;
		TagInfo info = {};
};

enum { TOK_TAG, TOK_END_TAG, TOK_OTHER };
struct token_t {
	int type;
	std::string str;
	//std::vector<ARG>
};

class HTMLLex {
		std::vector<token_t> token;
	public:
		HTMLLex() { }
		~HTMLLex() {}
		void lex(std::string);
		std::vector<token_t> &get_token();
};

class HTMLParser {
		vec_tag html;
		StyleLexer lexer;
		StyleParser parser;
	public:
		HTMLParser() { }
		~HTMLParser() {}
		TagBase *parse_tag(std::vector<token_t>::iterator&);
		void parse(std::vector<token_t>);
		vec_tag &get_html();
		void show(TagBase *);	
};

class Renderer {
		TagInfo *rendering(vec_tag::iterator&, TagInfo);
	public:
		Renderer() { }
		~Renderer() { }
		void rendering(vec_tag &);
};

