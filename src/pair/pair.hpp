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

	R &right() {
		return this->right_val;
	}

	Pair<L, R> &operator=(Pair<L, R> &p) {
		this->left_val = p.left();
		this->right_val = p.right();
		return *this;
	}

	bool operator==(Pair<L, R> &p) {
		return p.left() == this->left_val && p.right() == this->right_val;
	}
};

}

#endif // PAIR_HPP
