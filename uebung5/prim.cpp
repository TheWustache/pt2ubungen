
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>

/*
// test data: lecture example
static const auto N = static_cast<size_t>(6);
static const auto weights_table = std::array<int, N * N>{ {
	-1,  3, -1, -1,  6,  5,
	 3, -1,  1, -1, -1,  4,
	-1,  1, -1,  6, -1,  4,
	-1, -1,  6, -1,  8,  5,
	 6, -1, -1,  8, -1,  2,
	 5,  4,  4,  5,  2, -1 } };
	 */

	 ///*
	 // test data: city distances
	 // vertices are cities
	 // edges denote city connections
	 // weights denote travel distance



static const auto N = static_cast<size_t>(20);
// test data: city distances
static const auto weights_table = std::array<int, N * N>{ {
		-1, 255, 504, 477, 424, 512, 477, 422, 453, 315, 165, 149, 249, 378, 471, 439, 452, 336, 479, 398,
			255, -1, 612, 356, 393, 534, 338, 284, 308, 95, 377, 294, 132, 462, 321, 297, 320, 196, 370, 237,
			504, 612, -1, 456, 304, 190, 486, 477, 493, 582, 359, 360, 488, 150, 503, 486, 470, 483, 433, 510,
			477, 356, 456, -1, 152, 288, 34, 72, 57, 269, 474, 380, 249, 336, 56, 62, 37, 162, 25, 123,
			424, 393, 304, 152, -1, 152, 182, 177, 190, 329, 371, 293, 261, 187, 200, 184, 167, 212, 131, 218,
			512, 534, 190, 288, 152, -1, 322, 328, 335, 478, 412, 364, 401, 157, 342, 332, 311, 364, 264, 371,
			477, 338, 486, 34, 182, 322, -1, 57, 30, 248, 485, 389, 240, 363, 23, 41, 26, 150, 59, 101,
			422, 284, 477, 72, 177, 328, 57, -1, 32, 196, 439, 340, 182, 343, 49, 17, 36, 93, 90, 51,
			453, 308, 493, 57, 190, 335, 30, 32, -1, 217, 470, 371, 212, 364, 18, 14, 24, 122, 81, 70,
			315, 95, 582, 269, 329, 478, 248, 196, 217, -1, 405, 310, 100, 433, 229, 207, 231, 118, 285, 150,
			165, 377, 359, 474, 371, 412, 485, 439, 470, 405, -1, 100, 312, 259, 487, 456, 460, 375, 467, 434,
			149, 294, 360, 380, 293, 364, 389, 340, 371, 310, 100, -1, 214, 229, 389, 358, 363, 275, 375, 334,
			249, 132, 488, 249, 261, 401, 240, 182, 212, 100, 312, 214, -1, 338, 229, 199, 217, 90, 258, 151,
			378, 462, 150, 336, 187, 157, 363, 343, 364, 433, 259, 229, 338, -1, 377, 355, 343, 337, 318, 370,
			471, 321, 503, 56, 200, 342, 23, 49, 18, 229, 487, 389, 229, 377, -1, 32, 33, 138, 81, 84,
			439, 297, 486, 62, 184, 332, 41, 17, 14, 207, 456, 358, 199, 355, 32, -1, 26, 109, 84, 61,
			452, 320, 470, 37, 167, 311, 26, 36, 24, 231, 460, 363, 217, 343, 33, 26, -1, 128, 58, 85,
			336, 196, 483, 162, 212, 364, 150, 93, 122, 118, 375, 275, 90, 337, 138, 109, 128, -1, 175, 62,
			479, 370, 433, 25, 131, 264, 59, 90, 81, 285, 467, 375, 258, 318, 81, 84, 58, 175, -1, 142,
			398, 237, 510, 123, 218, 371, 101, 51, 70, 150, 434, 334, 151, 370, 84, 61, 85, 62, 142, -1
	} };
//*

int weight(const int i, const int j) // this encapsualtes acces to the table of weights
{
	assert(i < N);
	assert(j < N);

	assert(weights_table[i + j * N] == weights_table[i * N + j]);

	return weights_table[i + j * N];
}


struct Vertex
{
	Vertex(const int i = 0)
		: index(i)
		, key(max_key)
		, parent_index(undef)
		, deleted(false)
	{
	}

	int index;
	int key;
	int parent_index;
	int deleted;

	static const int max_key;
	static const int undef = -1;
};

const int Vertex::max_key = std::numeric_limits<int>::max();


struct Edge
{
	Edge(const int a, const int b)
		: vi1(a)
		, vi2(b)
		, weight(::weight(a, b)) { }

	int vi1;
	int vi2;
	int weight;
};

// vertex printing
std::ostream & operator<<(std::ostream & os, const Vertex & v)
{
	os << static_cast<char>('a' + v.index);
	return os;
}

// edge printing
std::ostream & operator<<(std::ostream & os, const std::vector<Edge> & E)
{
	os << "{";
	for (size_t i = 0, N = E.size(); i < N; ++i)
		os << (i > 0 ? "," : "") << "(" << static_cast<char>('a' + E[i].vi1) << "," << static_cast<char>('a' + E[i].vi2) << ")";
	os << "}";
	return os;
}

// construct a graph for a given city distance table
void createGraph(std::vector<Edge> & E, std::vector<Vertex> & V)
{
	//	5.1a: clear V and E and insert all vertices and edges
	// - every node should be stored only once
	// - no loops on nodes (edges between single nodes, i.e., edges with weight < 0)
	// - any edge of nodes a and b is bidirectional, so edge b to a is not required (no duplicates)
	E.clear();
	V.clear();
	for (int y = 0; y < N; y++) {
		V.push_back(Vertex(y));
		for (int x = y + 1; x < N; x++) {
			if (weight(y, x) != -1)
				E.push_back(Edge(y, x));
		}
	}
}

// return added weights of a list of edges
int totalWeight(const std::vector<Edge> & E)
{
	// 5.1b: total weight accumulated over the given edges
	int sum = 0;
	for (Edge e : E) {
		sum += e.weight;
	}
	return sum;
}


bool printed = false;

std::vector<Vertex>::iterator getMinKey(std::vector<Vertex>::iterator start, std::vector<Vertex>::iterator end) {
	//default = maxKey
	assert(start != end);
	auto minVertex = start;
	while (start != end) {
		if (start->key < minVertex->key)minVertex = start;
		start++;
	}
	return minVertex;
}
std::vector<Vertex*> getNeighbors(Vertex &v, std::vector<Vertex> &V, std::vector<Edge> &E) {
	bool isAdded[N]{ false };
	std::vector<Vertex*> neighborList(0);
	for (Edge e : E) {
		//check for Edges with Vertex v in it
		if (e.vi1 == v.index) {
			//check if already added to neighbors (not necessary but nice):
			if (!isAdded[e.vi2]) {
				for (int i = 0; i < V.size(); i++)
					//get corresponding Vertex if in V;
					if (V.at(i).index == e.vi2) {
						neighborList.push_back(&(V.at(i)));
						isAdded[e.vi2] = true;
						break;
					}
			}
		}
		else {
			if (e.vi2 == v.index) {
				if (!isAdded[e.vi2]) {
					for (int i = 0; i < V.size(); i++)
						if (V.at(i).index == e.vi1) {
							neighborList.push_back(&(V.at(i)));
							break;
							isAdded[e.vi2] = true;
						}					
				}
			}
		}
	}
	return neighborList;
}

int getRandomNumber() {
	return 1;	// chosen by a fair dice roll
				// guaranteed to be random
}

void prim()
{
	auto V = std::vector<Vertex>(N);
	auto E = std::vector<Edge>{ };

	// generate city graph based on distance table
	createGraph(E, V);
	// 5.1c: implement prim algorithm
	auto processQuere = V;
	//set starting vertex, randomly chosen 0
	processQuere.at(getRandomNumber()).key = 0;
	std::vector<Edge> mstEdges{};
	while (processQuere.size() > 0) {
		//get position and value of minVertex
		auto minIt = getMinKey(processQuere.begin(), processQuere.end());
		Vertex minVertex = *minIt;
		processQuere.erase(minIt);
		if (minVertex.parent_index != minVertex.undef) {
			mstEdges.push_back(Edge(minVertex.index, minVertex.parent_index));
		}
		//only neighbors in Q are needed
		for (Vertex * v : getNeighbors(minVertex, processQuere, E)) {
			//dont need to check if it is in Q, since neighbors are only chosen from q
			if (weight(v->index, minVertex.index) < v->key) {
				v->parent_index = minVertex.index;
				v->key = weight(v->index, minVertex.index);
			}
		}

	}

	std::cout << mstEdges << std::endl;
	std::cout << "total cost:" << totalWeight(mstEdges);

}


int main(int argc, char** argv)
{
	prim();

	return 0;
}