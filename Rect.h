/******************************************************************************************************************************************************************************************
File Name:  Rect.h
Author(s):  Joel Johnson
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#include "Advanced2D.h"

#pragma once
 
namespace GAM200
{
	class Rect
	{
		public:
			double left, top, right, bottom;

		public:
			Rect();
			Rect(int left, int top, int right, int bottom);
			Rect(double left, double top, double right, double bottom);
			virtual ~Rect() {}

			double getLeft() { return left; }
			double getTop() { return top; }
			double getRight() { return right; }
			double getBottom() { return bottom; }

			double getWidth() { return right - left; }
			double getHeight() { return bottom - top; }

			bool isInside(GAM200::Vector3 point);
			bool isInside(int x, int y);
			bool isInside(double x, double y);
	};
}
