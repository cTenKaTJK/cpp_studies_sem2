#pragma once

namespace mtetr {
	class Tetr {

		float edge_;

	public:

		Tetr(float edge);

		~Tetr();

		float get_edge();

		float get_square();

		float get_volume();

	};
}