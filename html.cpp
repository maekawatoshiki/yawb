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
void HTMLLex::lex(std::string str) {
	for(auto it = str.begin(); it != str.end(); ++it) {
		if(*it == '<') {
			bool is_end_tag = false;
			std::string tag_name;
			it++; if(*it == '/') { is_end_tag = true; it++; }
			while(*it != '>')
				tag_name += ::toupper(*(it++));
			token.push_back({is_end_tag ? TOK_END_TAG : TOK_TAG, tag_name});
		} else if(*it != '<' && !isblank(*it)) {
			std::string content;
			while(*it != '<')
				content += *(it++);
			it--;
			token.push_back({TOK_OTHER, content});
		}
	}
	for(auto it = token.begin(); it != token.end(); ++it) {
		std::cout << it->type << " " << it->str << std::endl;
	}
}
std::vector<token_t> &HTMLLex::get_token() { return token; }

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
TagBase *HTMLParser::parse_tag(std::vector<token_t>::iterator &it) {
	if(it->type == TOK_TAG) {
		it++; // tag
		TagBase *cont; std::vector<TagBase *> content;
		while((cont = parse_tag(it)) != nullptr) { 
			content.push_back(cont); 
			++it; //TOK_TAG_END
		}
		return new TagGENERAL(it->str, content);
	} else if(it->type == TOK_OTHER) {
		return new TagSTRING(it->str);
	}
	return nullptr;
}
void HTMLParser::parse(std::vector<token_t> token) {
	for(auto tok = token.begin(); tok != token.end(); ++tok) {
		if(tok->type == TOK_TAG) {
			TagBase *tag = parse_tag(tok);
			html.push_back(tag);
		}
	}
}
std::vector<TagBase *> &HTMLParser::get_html() { return html; }
void HTMLParser::show(TagBase *tag) {
	std::string name = tag->get_tag_name();
	if(name == "string")
		std::cout << ((TagSTRING *)tag)->content;
	else {
		std::cout << "<" << name << ">";
		for(auto t : ((TagGENERAL *)tag)->content)
			show(t);
		std::cout << "</" << name << ">";
	}
}
