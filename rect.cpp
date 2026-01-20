#include "rect.hpp"
#include <stdexcept>

topit::Rect::Rect(p_t pos, int w, int h) : rect{pos, {pos.x + w, pos.y + h}}, IDraw()
{
	if (w <= 0 or h <= 0){
		throw std::logic_error("bad rect");
	}
}

topit::Rect::Rect(p_t a, p_t b): Rect(a, b.x - a.x, b.y - a.y)
{}

topit::p_t topit::Rect::begin() const {
	return rect.aa;
}

topit::p_t topit::Rect::next(p_t prev) const {
	if (prev.x == rect.aa.x and prev.y < rect.bb.y){
		return {prev.x, prev.y + 1};
	}
	if (prev.y == rect.bb.y && prev.x < rect.bb.x){
		return {prev.x + 1, prev.y};
	}
	if (prev.x == rect.bb.x && prev.y > rect.aa.y) {
		return {prev.x, prev.y - 1};
	}
	if (prev.y  == rect.aa.y && prev.x > rect.aa.x){
		return {prev.x - 1, prev.y};
	}
	throw std::logic_error("bad impl");
}
