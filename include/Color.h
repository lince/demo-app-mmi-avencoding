/*
 * Body.h
 *
 *  Created on: Sep 3, 2010
 *      Author: caioviel
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <string>
using namespace std;

namespace br {
namespace ufscar {
namespace lince {
namespace xpta {
namespace demo {

class Color {
public:
	static const Color* SKIN_COLOR;
	static const Color* DARKBLUE_COLOR;
	static const Color* LIGHTBLUE_COLOR;

	public:
		Color(string name, float red, float blue, float green);
		Color(float red, float blue, float green);
		~Color();

		string getName();

		void paint();

	private:
		float red, blue, green;
		string name;

};


}
}
}
}
}

#endif /*COLOR_H_*/
