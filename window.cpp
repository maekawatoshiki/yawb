#include "window.hpp"

Window::Window() {
	Gtk::Label *label = new Gtk::Label;
	Pango::FontDescription msgfont;
	msgfont.set_size(80 * PANGO_SCALE);
	label->set_text("HelloWorld");
	label->set_line_wrap();
	label->modify_font(msgfont);
	labels.push_back(label);
	hbox.pack_start(*label);
	hbox.set_size_request(100,100);
	add(hbox);

	show_all_children();
	resize(300, 270);
}
