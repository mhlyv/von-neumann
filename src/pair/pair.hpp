#ifndef __PAIR_HPP__
#define __PAIR_HPP__

namespace pair {

template<typename L, typename R>
class Pair {
private:
	L l;
	R r;
public:
	Pair(L l, R r) : l(l), r(r) {
	}

	L &left() {
		return l;
	}

	R &right() {
		return r;
	}

	Pair<L, R> &operator=(Pair<L, R> &p) {
		l = p.left();
		r = p.right();
		return *this;
	}
};

}

#endif // __PAIR_HPP__
