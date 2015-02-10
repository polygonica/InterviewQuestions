#include <iostream>
#include <cstdio>
#include <vector>
#include <climits>
using namespace std;

//2015 Whitepages interview question

//the following code solves the following problem:
//there is an array of numbers:
//[6060241004]
//each of these numbers represents a perch in a canyon our flying adventurer can stand on, the number representing how far along the elements of the array he can fly. A 0 represents a dragon that will eat our adventurer.
//the question asks for a minimally sized sequence of indices the adventurer can choose to fly between such that they will get past the end.

//example input:
//6
//0
//6
//0
//2
//4
//1
//0
//0
//4

//example output:
//0, 5, 9, out

//the solution to this problem is a simple dynamic programming one, I think, and the rough solution is below
typedef struct {
	unsigned long dist;
	unsigned long index;
} distIndex;

int main(int argc, char** argv) {
	//read in vector
	vector<unsigned long> canyon;
	unsigned long buf = 0;
	int count = 0;
	while((count = scanf("%lu", &buf)) > 0) {
		canyon.push_back(buf);
	}

	printf("input: ");
	for (int i = 0; i < canyon.size(); i++) {
		printf("%lu, ", canyon[i]);
	}
	printf("\n");

	//compute dynamic programming array
	vector<distIndex> dynArray(canyon.size());
	for (int i = canyon.size()-1; i>=0; i--) {
		if (canyon[i] == 0) { // dragon
			dynArray[i] = {ULONG_MAX, 0};
		} else if ((canyon.size() - i) <= canyon[i]) { //exit
			dynArray[i] = {1, ULONG_MAX};
		} else {
			unsigned long minval = ULONG_MAX;
			unsigned long minindex = 0;
			for (int j=i+1; j<=i+canyon[i]; j++) {
				if (dynArray[j].dist < minval) {
					minval = dynArray[j].dist;
					minindex = j;
				}
			}
			dynArray[i] = {minval,minindex};
			if (dynArray[i].dist != ULONG_MAX)
				dynArray[i].dist++;
		}
	}

	printf("dynamic programming array result: ");
	for (int i = 0; i < dynArray.size(); i++) {
		printf("{%d, %d}", dynArray[i].dist, dynArray[i].index);
	}
	printf("\n");

	//print out result
	printf("solution: ");
	if (dynArray[0].index == 0) {
		printf("failure\n");
		return 0;
	} else {
		for (int i = 0; i != ULONG_MAX; i = dynArray[i].index) {
			printf("%d, ", i);
		}
		printf("out\n");
		return 0;
	}
	return 0;
}

