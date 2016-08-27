#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

enum {
	TAG_HTML,
	TAG_BODY,
	TAG_H,
	TAG_STRING,
};

class TagBase {
	public:
		TagBase() { }
		virtual std::string get_tag_name() = 0;
};
class TagGENERAL : public TagBase {
	public:
		TagGENERAL(std::string _name, std::vector<TagBase *> _content):tag_name(_name), content(_content) { }
		virtual std::string get_tag_name() { return tag_name; }
		std::vector<TagBase *> content;
		std::string tag_name;
};
class TagSTRING : public TagBase {
	public:
		TagSTRING(std::string _content):content(_content) { }
		virtual std::string get_tag_name() { return "string"; }
		std::string content;
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
		std::vector<TagBase *> html;
	public:
		HTMLParser() { }
		~HTMLParser() {}
		TagBase *parse_tag(std::vector<token_t>::iterator&);
		void parse(std::vector<token_t>);
		std::vector<TagBase *> &get_html();
		void show(TagBase *);	
};
