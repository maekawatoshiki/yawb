#include "window.hpp"

Window::Window() {
	add(layout);
	resize(400, 400);
}

void Window::create_new_label(std::string text, int x, int y, int font_size) {
	Gtk::Label *label = new Gtk::Label;
	Pango::FontDescription msgfont;
	msgfont.set_size(font_size * PANGO_SCALE);
	label->set_text(text);
	label->modify_font(msgfont);
	labels.push_back(label);
	layout.put(*label, x, y);
	show_all_children();
}

void Painter::paint(vec_tag::iterator &tag) {
	std::string name = (*tag)->get_tag_name();
	if(name == "string") {
		TagSTRING *str = (TagSTRING*)*tag;
		window->create_new_label(str->content, str->get_info()->rect.top.x, str->get_info()->rect.top.y, 14);
	} else {
		TagGENERAL *tg = (TagGENERAL *)*tag;
		for(auto t = tg->content.begin(); t != tg->content.end(); ++t)
			paint(t);
	}
}

void Painter::paint(vec_tag &tag) {
	for(auto t = tag.begin(); t != tag.end(); ++t) {
		paint(t);
	}
}
