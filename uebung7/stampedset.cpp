#include <iostream>
#include <assert.h>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;


template<class T, class stamp_type = unsigned long>
class StampedSet {
public:
	StampedSet() {}

	stamp_type add(const T& obj) {
		if (auto objectPos = stampMap.find(obj) == stampMap.end()) {
			stampMap.insert(make_pair(obj, vector<stamp_type>({ stampCount++ })));
		}
		else {
			stampMap.at(obj).push_back(stampCount++);
		}
		return stampCount - 1;
	}

	void erase(const T& obj) {
		assert(stampMap.find(obj) != stampMap.end());
		stampMap.erase(stampMap.find(obj));
	}

	unsigned long noOfObjects() const {
		return static_cast<unsigned long>(stampMap.size());
	}

	unsigned long noOfStamps() const {
		size_t size = 0;
		for (auto pair : stampMap) {
			size += pair.second.size();
		}
		return static_cast<unsigned long>(size);
	}

	bool containsObject(const T& obj) const {
		return (stampMap.find(obj) != stampMap.end());
	}

	bool containsStamp(const stamp_type& s) const {
		//costly operation
		for (std::pair<T, vector<stamp_type>> pair : stampMap) {
			for (stamp_type stamp : pair.second) {
				if (stamp == s)return true;
			}
		}

		return false;
	}

	const T& findObject(const stamp_type& s) const {
		for (auto pair : stampMap) {
			for (stamp_type stamp : pair.second) {
				if (stamp == s)return pair.first;
			}
		}
		return false;
	}

	stamp_type lastStamp(const T& obj) const {
		assert(stampMap.find(obj) != stampMap.end());
		return *(stampMap.at(obj).end() - 1);
	}

	stamp_type firstStamp(const T& obj) const {
		assert(stampMap.find(obj) != stampMap.end());
		return *(stampMap.at(obj).begin());
	}

	stamp_type nextStamp() const {
		return stampCount;
	}

	template<typename L>
	void process(const T& obj, L&& fct) {
		assert(stampMap.find(obj) != stampMap.end());
		std::vector<stamp_type>& tempVec = stampMap.at(obj);
		tempVec.erase(remove_if(tempVec.begin(), tempVec.end(), [obj, fct](stamp_type s) {return fct(obj, s); }), tempVec.end());
		if (tempVec.empty())
			add(obj);
	}


	template<typename L>
	void process(stamp_type from, stamp_type to, L&& fct) {
		if (to < from)return;
		for (auto& pair : stampMap) {
			std::vector<stamp_type>& tempVec = pair.second;
			const T& obj = pair.first;
			auto lowerBound = std::lower_bound(tempVec.begin(), tempVec.end(), from);
			auto upperBound = std::upper_bound(tempVec.begin(), tempVec.end(), to);
			if (upperBound != tempVec.end())
				upperBound++;
			//not as efficient as i want it but oh well
			tempVec.erase(remove_if(lowerBound, upperBound, [obj, fct, from, to](stamp_type s) {return fct(obj, s) && s>from && s<=to; }), tempVec.end());
				if (tempVec.empty())
					add(obj);
		}

	}

	stamp_type restart(const T& obj) {
		assert(stampMap.find(obj) != stampMap.end());
		auto& vector = stampMap.at(obj);
		vector.erase(vector.begin(), vector.end());
		vector.push_back(stampCount++);
		assert(vector.size() == 1);
		return stampCount - 1;
	}

private:
	stamp_type stampCount = 0;
	std::unordered_map<T, std::vector<stamp_type>> stampMap;
};


void test() {
	StampedSet<float, int> sfs;
	float f{ 0.0f };
	int s{ 0 };
	int z{ 0 };

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
	sfs.process(0, sfs.nextStamp(), [](float f, int i) { cout << "(" << f << ", " << i << ") "; return false; }); cout << endl;

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

	int N{ 0 };
	sfs.process(0, 100, [&N](float f, int i) { N++; return false; }); cout << "test " << "N: " << N << ", stamps: " << sfs.noOfStamps() << endl; assert(N == sfs.noOfStamps());

	// test process deletion
	
	f = 3.14f; sfs.process(f, [](float f, int i) { return true; }); assert(sfs.lastStamp(f) == 18);
	sfs.process(1, 7, [](float f, int i) { return f < 6.0f; });	assert(sfs.lastStamp(5.01f) == 19); assert(sfs.firstStamp(9.99f) == 1); assert(sfs.firstStamp(1.11f) == 8);

	// check different instantiations
	StampedSet<string, int> sss;
	StampedSet<char, unsigned long> scs;
}


int main(int, char**) {
	test();
	return 0;
}
