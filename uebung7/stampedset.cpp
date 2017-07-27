#include <iostream>
#include <assert.h>

#include <unordered_map>
#include <list>
#include <utility>
#include <set>

using namespace std;


template<class T, class stamp_type = unsigned long>
class StampedSet {
public:
	StampedSet() {}

	stamp_type add(const T& obj) {
        stampToObj.insert( make_pair(curStamp, obj) );
        // insert object if it hasn't been yet, otherwise add the stamp to its list
        if( objToStamp.count(obj) ) {
            objToStamp.at(obj).push_back(curStamp);
        }
        else {
            objToStamp.insert( make_pair( obj, list<stamp_type>({curStamp}) ) );
        }
        
        curStamp++;
        return curStamp - 1;
	}

	void erase(const T& obj) {
        // only erase if obj is in StampedSet
        if( objToStamp.count(obj) ) {
            // needs to be done for both maps
            for(auto it = stampToObj.begin(), ite = stampToObj.end(); it != ite;) {
                if((*it).second == obj) {
                    it = stampToObj.erase(it);
                }
                else {
                    ++it;
                }
            }
            
            objToStamp.erase( objToStamp.find(obj) );
        }
	}

	unsigned long noOfObjects() const {
        return objToStamp.size();
	}

	unsigned long noOfStamps() const {
        return stampToObj.size();
	}

	bool containsObject(const T& obj) const {
        return objToStamp.count(obj);
	}

	bool containsStamp(const stamp_type& s) const {
        return stampToObj.count(s);
	}

	const T& findObject(const stamp_type& s) const {
        assert( containsStamp(s) );
        return stampToObj.at(s);
	}

	stamp_type lastStamp(const T& obj) const {
        assert( containsObject(obj) );
        return objToStamp.at(obj).back();
	}

	stamp_type firstStamp(const T& obj) const {
        assert( containsObject(obj) );
		return objToStamp.at(obj).front();
	}

	stamp_type nextStamp() const {
        return curStamp;
	}

	template<typename L>
	void process(const T& obj, L&& fct) {
        assert( containsObject(obj) );
        // function parameters should be 'T, stamp_type'
        // do da processing
        list<stamp_type>& stampList = objToStamp.at(obj);
        for(auto it = stampList.begin(), ite = stampList.end(); it != ite;) {
            if( fct(obj, *it) ) {
                stampToObj.erase( stampToObj.find(*it) );
                it = stampList.erase(it);
            }
            else {
                ++it;
            }
        }
        
        // add stamp if all were removed
        if( stampList.empty() ) {
            add(obj);
        }
    }

	template<typename L>
	void process(stamp_type from, stamp_type to, L&& fct) {
        assert( from <= to );
        // set for keeping track of all objects that were processed
        set<T> processedObj;
        // function parameters should be 'T, stamp_type'
        // process dat stuff
        for(stamp_type s = from; s <= to; s++) {
            if( containsStamp(s) ) {
                T& obj = stampToObj.at(s);
                // only process each object once
                if( !processedObj.count(obj) ) {
                    // process all stamps of the object within the given range
                    list<stamp_type>& stampList = objToStamp.at(obj);
                    for(auto it = stampList.begin(), ite = stampList.end(); it != ite;) {
                        // if the cuurent stamp is already bigger than to, all of the following will be too
                        if(*it > to) {
                            break;
                        }
                        if(*it >= from) {
                            if( fct(obj, *it) ) {
                                stampToObj.erase( stampToObj.find(*it) );
                                it = stampList.erase(it);
                            }
                            else {
                                ++it;
                            }
                        }
                        else {
                            ++it;
                        }
                    }
                    // make sure obj has at least one stamp
                    if( stampList.empty() ) {
                        add(obj);
                    }
                }
                processedObj.insert(obj);
            }
        }
    }

	stamp_type restart(const T& obj) {
        assert( containsObject(obj) );
        erase(obj);
        return add(obj);
	}

private:
    // two maps so both the stamp and the object can be used to look up each other
    unordered_map<stamp_type, T> stampToObj;
    unordered_map<T, list<stamp_type>> objToStamp;
    
    stamp_type curStamp = 0;
};

void testierTest() {
    StampedSet<char, int> s;
    char c = 'X';
    char c2 = 'Y';
    char c3 = 'Z';
    
    int x = s.add(c);
    s.add(c2);
    int start = s.add(c3);
    s.add(c3);
    s.add(c);
    int fin = s.add(c);
    s.add(c3);
    
    s.process( c, [](char obj, int s){cout << "Obj: " << obj << " Stamp: " << s << "\n"; return false;});
    s.restart(c);
    s.process( c, [](char obj, int s){cout << "Obj: " << obj << " Stamp: " << s << "\n"; return false;});
    
    std::cout << "prolly works\n";
}

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
//    testierTest();
	return 0;
}
