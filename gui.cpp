/*
 * We use the cairo graphics library and render a png image of a graph of the given size
*/
#if defined(_MSC_VER)
#define _USE_MATH_DEFINES
#endif

#include <string>
#include <iostream>
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include "graph.hpp"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>

static int PADDING = 5;
static int SPACING = 20;

bool exists(const char* fname) {
	return access(fname, F_OK) != -1;
}

std::string build_name(std::string start_name) {
	std::string check_name = start_name + ".png";
	if (exists(check_name.c_str())) {
		return build_name(start_name + "1");
	} else {
		return check_name;
	}
}

int render_png(Graph* graph)
{
	int i_side = (graph->side_length - 1) * SPACING + PADDING;

	//Cairo ImageSurface. This one will be saved afterwards as a png file
	Cairo::RefPtr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, i_side + PADDING * 2, i_side + PADDING * 2);
	//Cairo Context.
	Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);

	cr->save(); // save the state of the context
	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->paint(); // fill image with the color
	cr->restore(); // color is back to black now

	//Storing state to start drawing
	cr->save();

	//setting brush color to black
	cr->set_source_rgb(0.0, 0.0, 0.0);

	cr->set_line_width(1.0);

	//drawing lines
	for (int i = 0; i < graph->side_length; i++) {
		for (int j = 0; j < graph->side_length; j++) {
			//for a current node
			Node* current = graph->matrix.at(i).at(j);
			//find all friends
			for (int k = 0; k < current->friends.size(); k++) {
				pair<int, int> current_friend = *std::next(current->friends.begin(), k);
				//Move brush to current node
				cr->move_to(current->coors.first * SPACING + PADDING, current->coors.second * SPACING + PADDING);
				//Draw a line to current friend
				cr->line_to(current_friend.first * SPACING + PADDING, current_friend.second * SPACING + PADDING);
				cr->stroke();
			}
		}
	}

	//setting brush color to red
	cr->set_source_rgb(1.0, 0.0, 0.0);

	//drawing vertices after lines are drawn
	for (int i = 0; i < graph->side_length; i++) {
		for (int j = 0; j < graph->side_length; j++) {
			Node* current = graph->matrix.at(i).at(j);
			cr->arc(current->coors.first * SPACING + PADDING, current->coors.second * SPACING + PADDING, 1.0, 0.0, 2.0 * M_PI);
			cr->stroke();
		}
	}

	cr->restore();

#ifdef CAIRO_HAS_PNG_FUNCTIONS

	std::string filename = build_name("result");
	surface->write_to_png(filename);

	std::cout << "Wrote png file \"" << filename << "\"" << std::endl;

#else

	std::cout << "You must compile cairo with PNG support for this example to work."
	          << std::endl;

#endif
}

int main(int argc, char* argv[]) {
	int size, p, q, r, ret = 0;
	if (5 == argc || 7 == argc)
	{
		ret += sscanf(argv[1], "%d", &size);
		ret += sscanf(argv[2], "%d", &p);
		ret += sscanf(argv[3], "%d", &q);
		ret += sscanf(argv[4], "%d", &r);
		if (argc == 7) {
			ret += sscanf(argv[5], "%d", &PADDING);
			ret += sscanf(argv[6], "%d", &SPACING);
		}
		if (ret != 4 && ret != 6) {
			cout << "Error in parsing arguments\n";
			return 0;
		}
		Graph g(size);
		g.set_p(p);
		g.set_q_r(q, r);
		render_png(&g);
	} else {
		cout << "Wrong number of arguments\n";
	}
	return 0;
}

