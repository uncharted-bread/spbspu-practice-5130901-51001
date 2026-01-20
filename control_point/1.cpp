#include <cstddef>
struct Stud {
	const char * fst;
	const char * snd;
	int year;
	int dep;
};

struct Subj {
	const char * name;
	size_t people, classes;
	const Stud * const * studs;
	const size_t * visited;
};
void copy(const Stud* const* s, size_t k, const Stud** r){
	for (size_t i = 0; i < k; ++i){
		r[i] = s[i];
	}
}
bool contains(const Stud* const s,size_t ;, const Stud* c){
	for (size_t i = 0; i < k; ++i){
		if (s[i] == c){
			return true;
		}
	}
	return false;
}
void cut(const Stud*** s, size_t k){
	const Stud** r = new const Stud*[k];
	for (size_t )
}
const Stud** stud_union(size_t r, const Stud*, const* s1, size_t k1, const Stud*, const* s2, size_t k2) {
	const Stud** uni = new const Stud*[k1 + k2];
	size_t count = 0;
	r = count;
	return uni;
}

const Stud** stud_union(size_t& r, const Subj& s1, const Subj& s2) {
	return stud_union(r, s1.studs, s1.people, s2.studs, s2.people);
}

const Stud** stud_union(size_t& r, const Subj* ss, size_t k) {
	if (!k) {
		r = 0;
		return nullptr;
	}
	size_t count = 0;
	const Stud** uni = stud_union(count, ss[0].studs, ss[0].people, nullptr, 0);
	for (size_t i = 0, i < k; ++i) { 
		try {
			size_t tmp_count = 0;
			const Stud** tmp = stud_union(tmp_count, uni, count, ss[i].studs, ss[i].people);
			delete [] uni;
			uni = tmp;
			count = tmp_count;
		} catch(...) {
			delete [] uni;
			throw;
		}
	}
	r = count;
	return uni;
}
const Stud** filter(size_t& r, const Stud* const* studs, size_t k, bool(*consition)(const Stud*)){
	const Stud** f = new const Stud*[k];
	size_t count = 0;
	for (size_t i = 0; i < k; ++i) {
		if (condition(studs[i])) {
			f[count[++] = studs[i];
		}
	}
	try{
		cut(&r, count);
	} catch(...){
		delete[] f;
		throw;
	}
	r = count;
	return f;
}
bool is_bach(const Stud* s){
	return s->year<5;
}
const Stud** stud_bac(size_t& r, const Subj* ss, size_t k)
{
	size_t count = 0;
	const Stud** tmp_f = filter(tmp_count, uni, count, is_bach);
	delete[] uni;
	uni = tmp_f;
	count = tmp_count;
	
}
