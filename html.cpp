#include "html.hpp"

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
				content += (*it == '\n') ? (it++, '\0') : *(it++);
			it--;
			token.push_back({TOK_OTHER, content});
		}
	}
	for(auto it = token.begin(); it != token.end(); ++it) {
		std::cout << it->type << " " << it->str << std::endl;
	}
}
std::vector<token_t> &HTMLLex::get_token() { return token; }

TagBase *HTMLParser::parse_tag(std::vector<token_t>::iterator &it) {
	if(it->type == TOK_TAG) {
		if(it->str == "STYLE") {
			it++; lexer.lexer(it->str); it++;
			parser.parse(lexer.get_token());
		} else {
		it++; // tag
		TagBase *cont; std::vector<TagBase *> content;
		while((cont = parse_tag(it)) != nullptr) { 
			content.push_back(cont); 
			++it; //TOK_TAG_END
		}
		return new TagGENERAL(it->str, content);
		}
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

TagInfo *Renderer::rendering(vec_tag::iterator &tag, TagInfo info) {
	std::cout << "parent size: " << info.rect.top.x<<"x" << info.rect.top.y << ":" << info.rect.size.x << "x" << info.rect.size.y << std::endl;
	std::string name = (*tag)->get_tag_name();
	std::cout << "curtag" << name << std::endl;

	TagInfo ti; 
	ti.rect.size.x = 200;
	ti.rect.size.y = (name == "BODY" || name == "HTML") ? info.rect.size.y : 0;
	(*tag)->set_info(ti);

	if(name == "BODY" || name == "HTML") {
		TagGENERAL *tb = (TagGENERAL *)*tag;
		int top_y = 0;
		for(auto t = tb->content.begin(); t != tb->content.end(); ++t) {
			auto csz = rendering(t, ti);
			csz->rect.top.y = top_y;
			top_y += (*t)->get_tag_name() == "BODY" ? 0 : csz->rect.size.y;
			std::cout << "topy:" << top_y << std::endl;
		}
	} else if(name != "string") {
		TagGENERAL *tb = (TagGENERAL *)*tag;
		int top_y = info.rect.top.y;
		for(auto t = tb->content.begin(); t != tb->content.end(); ++t) {
			auto csz = rendering(t, ti);
			ti.rect.size.y += csz->rect.size.y;
			csz->rect.top.y = top_y;
			std::cout << csz->rect.size.x << "x" << csz->rect.size.y << std::endl;
			top_y += csz->rect.size.y;
			std::cout << "topy:" << top_y << std::endl;
		}
		(*tag)->set_info(ti);
	} else {
		TagSTRING *ts = (TagSTRING *)*tag;
		TagInfo tinf;
		tinf.rect.top.x = info.rect.top.x;
		tinf.rect.top.y = info.rect.top.y;
		tinf.rect.size.x = 50;
		tinf.rect.size.y = info.rect.size.y;
		ts->set_info(tinf);
	}
	return (*tag)->get_info();
}
void Renderer::rendering(vec_tag &tags) {
	TagInfo html_tag = {};
	html_tag.rect.size.x = 300;
	html_tag.rect.size.y = 300;
	for(auto tag = tags.begin(); tag != tags.end(); ++tag) {
		rendering(tag, html_tag);
	}
}
