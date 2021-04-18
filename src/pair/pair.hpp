#ifndef PAIR_HPP
#define PAIR_HPP

namespace pair {

template<typename L, typename R>
class Pair {
private:
	L left_val;
	R right_val;
public:
	Pair() {
	}

	Pair(L l, R r) : left_val(l), right_val(r) {
	}

	L &left() {
		return this->left_val;
	}

	L left() const {
		return this->left_val;
	}

	R &right() {
		return this->right_val;
	}

	R right() const {
		return this->right_val;
	}

	bool operator==(const Pair<L, R> &p) const {
		return p.left() == this->left_val && p.right() == this->right_val;
	}

	bool operator!=(const Pair<L, R> &p) const {
		return !(*this == p);
	}
};

}

#endif // PAIR_HPP
