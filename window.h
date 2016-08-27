#pragma once
#include <gtkmm.h>

class Window : public Gtk::Window {
		std::vector<Gtk::Label *> labels;
	public:
		Window();
		virtual ~Window() {
			for(auto l : labels)
				delete l;
		}
};
