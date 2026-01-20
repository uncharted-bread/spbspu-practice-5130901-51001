#include <iostream>
#include <stdexcept>
#include "ascii_draw.hpp"
namespace topit {
    struct Vline : IDraw {
    	explicit Vline(p_t start, int lenght);
    	p_t begin() const override;
    	p_t next(p_t prev) const override;
    	p_t start_point;
    	int len;
    };
    struct Square : IDraw {
    	explicit Square(p_t start, int ed);
    	p_t begin() const override;
    	p_t next(p_t prev) const override;
    	p_t start_point;
    	int edge;
    };
}

int main() {
	using namespace topit;
	int err = 0;
    IDraw* shp[5] = {};
	Layers layers;
    try{
	    shp [0] = new Rect({-3, 4}, 4, 6);
	    shp [1] = new FRect({3, 4}, 6, 3);
	    shp [2] = new Dot({-5, -2});
	    shp [3] = new Vline({-2, 0}, 5);
	    shp [4] = new Square({1, 1}, 4);
		for (size_t i = 0; i < 5; ++i){
			layers.append(*(shp[i]));
		}
		f_t fr = layers.frame();
		char * cnv = canvas(fr, '.');
		const char * brush = "#0%$*";
		for (size_t k = 0; k < layers.layers(); ++k){
			size_t start = layers.start(k);
			size_t end = layers.end(k);
			for (size_t i = start; i < end; ++i){
				paint(layers.point(i), cnv, fr, brush[k]);
			}	
		}
	    flush (std::cout, cnv, fr);
	    delete[] cnv;
	} catch (...){
		std::cerr << "Error!\n";
		err = 1;
	}
    delete shp[1];
    delete shp[2];
    delete shp[0];
    delete shp[3];
    delete shp[4];
    return err;
}



topit::Vline::Vline(p_t start, int lenght):
  start_point(start),
  len(lenght) {
  	if (len <= 0){
  		throw std::logic_error("Lenght must be > 0");
  	}
}

topit::p_t topit::Vline::begin() const {
	return start_point;
}

topit::p_t topit::Vline::next(p_t prev) const {
    if (prev == start_point) {
        if (len > 1) {
            return {start_point.x, start_point.y + 1};
        }
        return start_point;
    }
    
    int current_index = prev.y - start_point.y;
    if (current_index < len - 1) {
        return {prev.x, prev.y + 1};
    }
    
    return start_point;
}

topit::Square::Square(p_t start, int ed) :
	start_point(start),
	edge(ed)
{
	if (edge <= 0) {
		throw std::logic_error("Edge lenght must be > 0");
	}
}

topit::p_t topit::Square::begin() const {
    return start_point;
}
topit::p_t topit::Square::next(p_t prev) const {    
    if (edge == 1) {
        return start_point;
    }
    int dx = prev.x - start_point.x;
    int dy = prev.y - start_point.y;
    if (dy == 0 && dx < edge - 1) {
        return {prev.x + 1, prev.y};
    }
    if (dx == edge - 1 && dy == 0) {
        return {prev.x, prev.y + 1};
    }
    if (dx == edge - 1 && dy < edge - 1) {
        return {prev.x, prev.y + 1};
    }
    if (dx == edge - 1 && dy == edge - 1) {
        return {prev.x - 1, prev.y};
    }
    if (dy == edge - 1 && dx > 0) {
        return {prev.x - 1, prev.y};
    }
    if (dx == 0 && dy == edge - 1) {
        return {prev.x, prev.y - 1};
    }
    if (dx == 0 && dy > 1) {
        return {prev.x, prev.y - 1};
    }
    return start_point;
}
