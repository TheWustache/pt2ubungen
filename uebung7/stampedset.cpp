#include <iostream>
#include <assert.h>

using namespace std;


template<class T, class stamp_type = unsigned long>
class StampedSet {
public:
	StampedSet() {}

	stamp_type add(const T& obj) {
		// TODO
	}

	void erase(const T& obj) {
		// TODO
	}

	unsigned long noOfObjects() const {
		// TODO
	}

	unsigned long noOfStamps() const {
		// TODO
	}

	bool containsObject(const T& obj) const {
		// TODO
	}

	bool containsStamp(const stamp_type& s) const {
		// TODO
	}

	const T& findObject(const stamp_type& s) const {
		// TODO
	}

	stamp_type lastStamp(const T& obj) const {
		// TODO
	}

	stamp_type firstStamp(const T& obj) const {
		// TODO
	}

	stamp_type nextStamp() const {
		// TODO
	}

	template<typename L>
	void process(const T& obj, L&& fct) {
		// TODO
	}

	template<typename L>
	void process(stamp_type from, stamp_type to, L&& fct) {
		// TODO
	}

	stamp_type restart(const T& obj) {
		// TODO
	}

private:
	// TODO
};


void test() {
	StampedSet<float, int> sfs;
	float f {0.0f};
	int s {0};
	int z {0};

	// check add, containsObject, containsStamp
	f = 3.14f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 9.99f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 5.01f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 3.14f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 9.99f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 3.14f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 3.14f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 1.11f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));
	f = 1.11f; s = sfs.add(f); assert(sfs.containsStamp(s)); assert(sfs.containsObject(f));

	// test process by lambda that prints contents
	sfs.process(0, sfs.nextStamp(), [](float f, int i){ cout << "(" << f << ", " << i << ") "; return false; }); cout << endl;

	// check erase
	f = 8.12f; s = sfs.add(f); sfs.erase(f); assert(!sfs.containsStamp(s)); assert(!sfs.containsObject(f));

	// test assignment of next stamp to next added object
	z = sfs.nextStamp(); f = 2.22f; s = sfs.add(f); assert(s == z);

	// test restart
	f = 2.22f; sfs.add(f); sfs.add(f); z = sfs.nextStamp(); s = sfs.restart(f); assert(s == z);

	// check first/last stamps
	f = 2.33f; s = sfs.add(f); assert(s == sfs.firstStamp(f)); assert(s == sfs.lastStamp(f));
	f = 2.44f; s = sfs.add(f); z = sfs.add(f); assert(s == sfs.firstStamp(f)); assert(z == sfs.lastStamp(f));

	// check find object
	f = 2.55f; s = sfs.add(f); assert(f == sfs.findObject(s));

	int N {0};
	sfs.process(0, 100, [&N](float f, int i){ N++; return false; }); cout << "N: " << N << ", stamps: " << sfs.noOfStamps() << endl; assert(N == sfs.noOfStamps());

	// test process deletion
	f = 3.14f; sfs.process(f, [](float f, int i){ return true; }); assert(sfs.lastStamp(f) == 18);
	sfs.process(1, 7, [](float f, int i){ return f < 6.0f; }); assert(sfs.lastStamp(5.01f) == 19); assert(sfs.firstStamp(9.99f) == 1); assert(sfs.firstStamp(1.11f) == 8);

	// check different instantiations
	StampedSet<string, int> sss;
	StampedSet<char, unsigned long> scs;
}


int main(int,char**) {
	test();
	return 0;
}
