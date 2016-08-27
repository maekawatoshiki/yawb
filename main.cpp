#include "html.hpp"
#include "window.hpp"
#include <gtkmm.h>

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	Window win;
	HTMLLex lex;
	HTMLParser parser;
	lex.lex("<html><body><h1>title</h1>this is a content in the body</body></html>");
	parser.parse(lex.get_token());
	parser.show(parser.get_html()[0]);

	// Gtk::Main::run(win);
}
