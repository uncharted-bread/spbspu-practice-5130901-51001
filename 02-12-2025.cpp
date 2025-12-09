#include <iostream>
#include <stdexcept>
namespace topit {

    struct p_t {
        int x, y;
    };

    struct f_t {
        p_t aa, bb;
    };
    size_t rows(f_t fr);
    size_t cols(f_t fr);
    bool operator==(p_t a, p_t b);
    bool operator!=(p_t a, p_t b);

    struct IDraw {
        virtual ~IDraw() = default;
        virtual p_t begin() const = 0;
        virtual p_t next(p_t prev) const = 0;
    };
    p_t* extend(const p_t* pts, size_t s, p_t fill);
    void extend(p_t** pts, size_t& s, p_t fill);
    struct Dot : IDraw {
        explicit Dot(p_t dd);
        p_t begin() const override;
        p_t next(p_t prev) const override;
        p_t d;
    };
    struct Vline : IDraw {
        explicit Vline(p_t start, int length);
        p_t begin() const override;
        p_t next(p_t prev) const override;
        p_t start_point;
        int len;
    };
    struct Rect: IDraw {
    	Rect(p_t pos, int w, int h);
    	Rect(p_t a, p_t b);
    	p_t begin() const override;
    	p_t next(p_t prev) const override;
    	f_t rect;
    };
    struct FRect: IDraw {
    	FRect (p_t pos, int w, int h);
    	FRect(p_t a, p_t b);
    	p_t begin() const override;
    	p_t next(p_t prev) const override;
    	f_t rect;
    }
    void append(const IDraw* sh, p_t** ppts, size_t& s);
    f_t frame(const p_t* pts, size_t s);
    char* canvas(f_t fr, char fill);
    void paint(p_t p, char* cnv, f_t fr, char fill);
    void flush(std::ostream& os, const char* cnv, f_t fr);

    struct Layers{
    	void append(const IDraw & dr);
    	size_t points() const;
    	size_t layers() const;
    	size_t layer(size_t i) const;
    	p_t point(size_t i) const;
    	private:
    	size_t points_;
    	p_t * pts_;
    	size_t layers_;
    	size_t * sizes_;
    };
}

int main() {
    using namespace topit;
    int err = 0;
    IDraw* shp[4] = {};
    Layers layers;
    try {
        shp[0] = new Dot({ 0, 0 });
        shp[1] = new Rect({ 2, 3 }, {7,4});
        shp[2] = new FRect({-10, -4}, {7,7});
        shp[3] = new Vline({ -2, -4 }, 8);
        for (size_t i = 0; i < 4; ++i) {
            layers.append(shp[i], &pts, s);
        }
        f_t fr = frame(pts, s);
        char* cnv = canvas(fr, '.');
       const char * bruch[3] - "#%0";
        for (size_t k = 0; k < s; ++k) {
        	size_t start = layers.start(k);
        	size_t end - layers.end(k);
            paint(pts[i], cnv, fr, '#');
            for (size_t i = 0; i<s; ++i){
            	paint(pts[i], cnv, fr, brush[k]);
            }
        }
        flush(std::cout, cnv, fr);
        delete[] cnv;
    }
    catch (...) {
        std::cerr << "Error!\n";
        err = 1;
    }
    delete shp[3];
    delete shp[2];
    delete shp[1];
    delete shp[0];
    return err;
}
void topit::Layers::append::(const IDraw& dr){
	append(&dr, &pts_, points_);
	size_t ext_sizes = new size_t[layers_ + 1];
	try{
		append(&dr, &pts_, points_);
	} catch(...){
		delete [] ext_sizes;
		throw;
	}
	for (size_t i = 0; i < layers_; ++i){
		ext_sizes[i] = sizes_[i];
	}
	ext_sizes[layers_] = points_;
	delete [] sizes_;
	sizes_ - ext_sizes;
	++layers_;
}
void topit::paint(p_t p, char* cnv, f_t fr, char fill)
{
    size_t dx = p.x - fr.aa.x;
    size_t dy = fr.bb.y - p.y;
    cnv[dy * cols(fr) + dx] = fill;
}

topit::p_t* topit::extend(const p_t* pts, size_t s, p_t fill)
{
    p_t* r = new p_t[s + 1];
    for (size_t i = 0; i < s; i++) {
        r[i] = pts[i];
    }
    r[s] = fill;
    return r;
}

void topit::extend(p_t** pts, size_t& s, p_t fill)
{
    p_t* r = extend(*pts, s, fill);
    delete[] * pts;
    ++s;
    *pts = r;
}

void topit::append(const IDraw* sh, p_t** ppts, size_t& s)
{
    extend(ppts, s, sh->begin());
    p_t b = sh->begin();

    while (sh->next(b) != sh->begin()) {
        b = sh->next(b);
        extend(ppts, s, b);
    }
}

void topit::flush(std::ostream& os, const char* cnv, f_t fr)
{
    for (size_t i = 0; i < rows(fr); ++i) {
        for (size_t j = 0; j < cols(fr); ++j) {
            os << cnv[i * cols(fr) + j];
        }
        os << '\n';
    }
}

char* topit::canvas(f_t fr, char fill)
{
    size_t s = rows(fr) * cols(fr);
    char* c = new char[s];
    for (size_t i = 0; i < s; ++i) {
        c[i] = fill;
    }
    return c;
}

topit::f_t topit::frame(const p_t* pts, size_t s)
{
    int minx = pts[0].x;
    int miny = pts[0].y;
    int maxx = pts[0].x;
    int maxy = pts[0].y;
    for (size_t i = 0; i < s; ++i) {
        minx = std::min(minx, pts[i].x);
        miny = std::min(miny, pts[i].y);
        maxx = std::max(maxx, pts[i].x);
        maxy = std::max(maxy, pts[i].y);
    }
    p_t a{ minx, miny };
    p_t b{ maxx, maxy };
    return f_t{ a, b };
}
topit::FRect::FRect(p_t pos, int w, int h):
	IDraw(),
	rect{pos, {pos.x + w, pos.y + h}}
{
	if (!(w > 0 && h > 0)) {
		throw std::logic_error("bad filled rect");
	}
}

topit::FRect::FRect(p_t a, p_t b):
	FRect(a, b.x - a.x, b.y - a.y)
{}

topit::p_t topit::FRect::begin() const {
	return r
}

topit::p_t topit::FRect::next(p_t prex) const {
	if (prev.x < rect.bb.x) {
		return {prev.x + 1, prev.y};
	} else if (prev.x == rect.bb.x && prev.y < rect.bb.y) {
		return {prev.aa.x , prev.y + 1};
	} else if (prev == rect.bb){
		return rect.aa;
	}
	throw std::logic_error("bad impl");
}

topit::Rect::Rect(p_t pos, int w, int h):
	IDraw(),
	rect{pos, {pos.x + w, pos.y + h}}
{
	if (!(w > 0 && h > 0)) {
		throw std::logic_error("bad rect");
	}
}
topit::Rect::Rect(p_t a, p_t b):
	Rect(a, b.x - a.x, b.y - a.y)
{}

topit::p_t topit::Rect::begin() const {
	return rect.aa;
}
topit::p_t topit::Rect::next(p_t prex) const {
	if (prev.x == rect.aa.x && prev.y < prev.bb.y) {
		return {prev.x, prev.y + 1};
	} else if (prev.y == rect.bb.y && prev.x < rect.bb.x) {
		return {prev.x +1, prev.y};
	} else if (prev.x == rect.bb.x && prev.y > rect.aa.y){
		return{prev.x, prev.y - 1};
	} else if (prev.y == rect.aa.y && prev.x > rect.aa.x) {
		return{prev.x -  1, prev.y}
	}
	throw std::logic_error("bad impl");
}

topit::Dot::Dot(p_t dd) :
    IDraw(),
    d{ dd }
{
}

topit::p_t topit::Dot::begin() const {
    return d;
}

topit::p_t topit::Dot::next(p_t prev) const {
    if (prev != d) {
        throw std::logic_error("bad prev");
    }
    return d;
}

bool topit::operator==(p_t a, p_t b) {
    return a.x == b.x && a.y == b.y;
}

bool topit::operator!=(p_t a, p_t b) {
    return !(a == b);
}

size_t topit::rows(f_t fr)
{
    return fr.bb.y - fr.aa.y + 1;
}
size_t topit::cols(f_t fr)
{
    return fr.bb.x - fr.aa.x + 1;
}

topit::Vline::Vline(p_t start, int length) :
    start_point(start),
    len(length) {
    if (len <= 0) {
        throw std::logic_error("Length must be > 0");
    }
}

topit::p_t topit::Vline::begin() const {
    return start_point;
}

topit::p_t topit::Vline::next(p_t prev) const {
    if (prev == start_point) {
        if (len > 1) {
            return { start_point.x, start_point.y + 1 };
        }
        return start_point;
    }

    int current_index = prev.y - start_point.y;
    if (current_index < len - 1) {
        return { prev.x, prev.y + 1 };
    }

    return start_point;
}
