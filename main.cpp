#include "html.hpp"
#include "window.hpp"
#include <gtkmm.h>

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	Window win;
	HTMLLex lex;
	HTMLParser parser;
	Renderer render;
	// lex.lex("<html><body><h1>title</h1>this <p>HELLO</p> is a content in the body</body></html>");
	lex.lex("<html><body><h1>title</h1></body></html>");
	parser.parse(lex.get_token());
	parser.show(parser.get_html()[0]);
	render.rendering(parser.get_html());

	Gtk::Main::run(win);
}
