#include <iostream>
#include <assert.h>
#include <unordered_map>
#include <set>
#include <list>
#include <algorithm>

using namespace std;


template<class T, class stamp_type = unsigned long>
class StampedSet {
public:
	StampedSet() {}

	stamp_type add(const T& obj) {
		int num = noOfStamps();
		if (auto objectPos = stampMap.find(obj) == stampMap.end()) {
			stampMap.insert(make_pair(obj, list<stamp_type>({ stampCount })));
		}
		else {
			stampMap.at(obj).push_back(stampCount);
		}
		helperMap.insert(make_pair(stampCount++, obj));
		assert(num == noOfStamps() - 1);
		return stampCount - 1;
	}

	void erase(const T& obj) {
		//assert(stampMap.find(obj) != stampMap.end()); moved to if-statement to be more user friendly;
		if (stampMap.count(obj)) {
			//erase out of both maps
			for (auto it = helperMap.cbegin(); it != helperMap.cend();) {
				if ((*it).second == obj)
					it = helperMap.erase(it);
				else
					++it;
			}
			stampMap.erase(stampMap.find(obj));
		}
		assert(!stampMap.count(obj));
	}

	unsigned long noOfObjects() const {
		return static_cast<unsigned long>(stampMap.size());
	}

	unsigned long noOfStamps() const {
		unsigned long size = static_cast<unsigned long>(helperMap.size());
		assert(noOfObjects() <= size);
		return size;
	}

	bool containsObject(const T& obj) const {
		return (stampMap.count(obj));
	}

	bool containsStamp(const stamp_type& s) const {
		return helperMap.count(s);
	}

	const T& findObject(const stamp_type& s) const {
		assert(containsStamp(s));
		return(helperMap.at(s));
	}

	stamp_type lastStamp(const T& obj) const {
		assert(containsObject(obj));
		return stampMap.at(obj).back();
	}

	stamp_type firstStamp(const T& obj) const {
		assert(containsObject(obj));
		return stampMap.at(obj).front();
	}

	stamp_type nextStamp() const {
		return stampCount;
	}

	template<typename L>
	void process(const T& obj, L&& fct) {
		assert(containsObject(obj));
		std::list<stamp_type>& tempList = stampMap.at(obj);
		for (auto it = tempList.begin(); it != tempList.end();) {
			if (fct(obj, *it)) {
				//remove out of both maps if needed
				helperMap.erase(*it);
				it = tempList.erase(it);
			}
			else {
				it++;
			}
		}
		//if all were deleted
		if (tempList.empty()) {
			add(obj);
		}
		assert(tempList.size() > 0);
	}
	//not fast enouth :(
	//tempVec.erase(remove_if(tempVec.begin(), tempVec.end(), [obj, fct](stamp_type s) {return fct(obj, s); }), tempVec.end()); 


	template<typename L>
	void process(stamp_type from, stamp_type to, L&& fct) {
		if (to < from)return;//could be made an assertion
		std::set<T> objQuere;
		//look for objects to process in order to not check them twice
		for (stamp_type i = from; i <= to; i++) {
			auto tIt = helperMap.find(i);
			if(tIt != helperMap.end()){
			T tempObj = tIt->second;
			if (objQuere.find(tempObj) == objQuere.end())
				objQuere.insert(tempObj);
			}
		}
		//process all objects
		for (T tempObj : objQuere) {
			std::list<stamp_type>& tempList = stampMap.at(tempObj);
			for (auto it = tempList.begin(); it != tempList.end();) {
				//stop as soon as possible
				if (*it > to)break;
				if (*it >= from) {
					if (fct(tempObj, *it)) {
						//delete if necessary
						helperMap.erase(*it);
						it = tempList.erase(it);
					}
					else {
						it++;
					}
				}
				else {
					it++;
				}
			}
			if (tempList.empty()) {
				add(tempObj);
			}
		}
	}

	stamp_type restart(const T& obj) {
		assert(containsObject(obj));
		erase(obj);
		add(obj);
		return stampCount - 1;
	}

private:
	stamp_type stampCount = 0;
	std::unordered_map<stamp_type, T> helperMap;
	std::unordered_map<T, std::list<stamp_type>> stampMap;
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
	sfs.process(0, 100, [&N](float f, int i) { N++; return false; }); cout << "N: " << N << ", stamps: " << sfs.noOfStamps() << endl; assert(N == sfs.noOfStamps());

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
