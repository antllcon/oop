#ifndef ICANVASDRAWABLE_H
#define ICANVASDRAWABLE_H

#include "../class-canvas/ICanvas.h"

class ICanvas;

class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;
};

#endif // ICANVASDRAWABLE_H