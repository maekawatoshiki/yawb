#pragma once
#include <gtkmm.h>

class Painter {
	public:

};

class Window : public Gtk::Window {
		std::vector<Gtk::Label *> labels;
		Gtk::HBox hbox;
	public:
		Window();
		virtual ~Window() {
			for(auto l : labels)
				delete l;
		}
};
