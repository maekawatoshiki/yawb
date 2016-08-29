#pragma once
#include <gtkmm.h>
#include "html.hpp"

class Window : public Gtk::Window {
		std::vector<Gtk::Label *> labels;
		Gtk::Layout layout;
	public:
		Window();
		virtual ~Window() { for(auto l : labels) delete l; }
		void create_new_label(std::string text, int x, int y, int font_size);
};

class Painter {
	public:
		Window *window;
		Painter(Window *win):window(win) { };
		void paint(vec_tag::iterator &);
		void paint(vec_tag &);
};

