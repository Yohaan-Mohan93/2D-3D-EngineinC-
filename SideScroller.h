#include "Advanced2D.h"
#pragma once

namespace GAM200
{
	class SideScroller
	{
	private:
		double scrollx;
		Texture *image;
		Rect viewport;
		D3DCOLOR color;

	public:
		SideScroller();
		virtual ~SideScroller();
		bool load(std::string filename);
		void setViewport(Rect rect) { viewport = rect; }
		void setViewport(double left, double right, double top, double bottom);
		void setColor(D3DCOLOR col) { color = col; }
		void update(double velocity);
		void draw();
		double getScrollPosition() { return scrollx; }

	};
}
