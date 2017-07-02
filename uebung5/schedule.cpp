//
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

#ifdef _WIN32
std::string block = std::string(char(219));
#else
std::string block = "\u2588";
#endif

struct Interval
{
	Interval(const int i, const int start, const int length)
	: index(i)
	, start(start)
	, end(start + length - 1)
	{
	}

	int index;
	int start;
	int end;
};

const static int MaxEnd = 74;
const static int MaxDuration = 10;

const static int N = 20;

std::ostream & operator<<(std::ostream & os, const std::vector<Interval> & I)
{
	// Todo 5.3: Implement a nice print function
    for( int j=0; j < I.size(); j++ ) {
        // one line
        os << "#" << I[j].index << ( I[j].index < 10 ? "  " : " " ) << "|";
        for( int k=0; k < MaxEnd; k++ ) {
            os << ( k >= I[j].start && k <= I[j].end ? block : "." );
        }
        os << "|" << std::endl;
    }
	//os << I.size() << std::endl;
	return os;
}

// creates random data
void randomize(std::vector<Interval> & intervals)
{
	intervals.clear();
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < N; i++)
	{
		int duration = rand() % MaxDuration + 1;
		int start = rand() % (MaxEnd - duration + 2);

		intervals.push_back(Interval(i, start, duration));
	}
}

void schedule(const std::vector<Interval> & intervals)
{
	std::cout << std::endl << "intervals (randomized):" << std::endl << intervals;


	// Todo 5.3: Sort intervals
    auto sorted = intervals;
    std::sort( sorted.begin(), sorted.end(), []( const Interval &a, const Interval &b ){ return a.end < b.end; });
    
    std::cout << std::endl << "intervals (sorted):" << std::endl << sorted;


	// Todo 5.3: Implement greedy scheduling
	auto scheduled = std::vector<Interval>();
    
    // insert intervall with smallest end time
    scheduled.push_back(sorted[0]);
    for( auto iter = sorted.begin()++; iter != sorted.end(); iter++ ) {
        if( scheduled[ scheduled.size()-1 ].end < (*iter).start ) {
            scheduled.push_back(*iter);
        }
    }


	std::cout << std::endl << "intervals (scheduled, " << scheduled.size() << " of " << sorted.size() << " possible)"
		<< std::endl << scheduled << std::endl;
}

int main(int argc, char** argv) {

	auto intervals = std::vector<Interval>();

	randomize(intervals);
	schedule(intervals);

	return 0;
}
