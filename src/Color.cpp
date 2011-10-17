#include "../include/Color.h"

#include <GL/glu.h>

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

Color::Color(string name, float red, float blue, float green) {
	this->name = name;
	this->red = red;
	this->blue = blue;
	this->green = green;
}

Color::Color(float red, float blue, float green) {
	Color("noname", red, blue, green);
}

Color::~Color() {

}

void Color::paint() {
	glColor3f(red,blue,green);
}

const Color* Color::SKIN_COLOR = new Color("skin", 0.90589,0.76078,0.68235);
const Color* Color::DARKBLUE_COLOR = new Color("darkblue", 0.45490,0.78039,0.96471);
const Color* Color::LIGHTBLUE_COLOR = new Color("lightblue", 0.16863,0.13333,0.65490);

}
}
}
}
}
