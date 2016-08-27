#include "window.hpp"

Window::Window() {
	Gtk::Label *label = new Gtk::Label;
	Pango::FontDescription msgfont;
	msgfont.set_size(100 * PANGO_SCALE);
	label->set_text("Hello World");
	label->modify_font(msgfont);
	labels.push_back(label);
	add(*labels.back());

	show_all_children();
	resize(300, 270);
}
