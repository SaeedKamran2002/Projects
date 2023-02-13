#include<iostream>
#include<float.h>
#include<math.h>
#include <pthread.h>
#include<stack>
#include<cstring>
#include<set>
#include <sys/time.h>
#include <pthread.h>
using namespace std;

#define ROW 9
#define COL 10

typedef pair<int, int> Pair;

typedef pair<double, pair<int, int> > pPair;

struct timeval initial, final;
struct cell {

	int parent_i, parent_j;

	double f, g, h;
};
cell cellDetails[ROW][COL];
bool closedList[ROW][COL];
set<pPair> openList;
bool foundDest = false;
double gNew, hNew, fNew;
int i, j;
int grid[ROW][COL]= { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
					{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
					{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
					{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
					{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
					{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
					{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
					{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
					{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };


Pair src = make_pair(8, 0);


Pair dest = make_pair(0, 0);


void *north(void *arg);
void *South(void *arg);
void *east(void *arg);
void *west(void *arg);
void *northEast(void *arg);
void *northWest(void *arg);
void *southEast(void *arg);
void *southWest(void *arg);
bool isValid(int row, int col)
{
	return (row >= 0) && (row < ROW) && (col >= 0)
		&& (col < COL);
}


bool isUnBlocked(int grid[][COL], int row, int col)
{

	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}


bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

double calculateHValue(int row, int col, Pair dest)
{

	return ((double)sqrt(
		(row - dest.first) * (row - dest.first)
		+ (col - dest.second) * (col - dest.second)));
}


void tracePath(cell cellDetails[][COL], Pair dest)
{
//	printf("\nThe Path is ");
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row
			&& cellDetails[row][col].parent_j == col)) {
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	while (!Path.empty()) {
		pair<int, int> p = Path.top();
		Path.pop();
//		printf("-> (%d,%d) ", p.first, p.second);
	}

	return;
}


void aStarSearch(int grid[][COL], Pair src, Pair dest)
{

	if (isValid(src.first, src.second) == false) {
		printf("Source is invalid\n");
		return;
	}

	if (isValid(dest.first, dest.second) == false) {
		printf("Destination is invalid\n");
		return;
	}


	if (isUnBlocked(grid, src.first, src.second) == false
		|| isUnBlocked(grid, dest.first, dest.second)
			== false) {
		printf("Source or the destination is blocked\n");
		return;
	}

	if (isDestination(src.first, src.second, dest)
		== true) {
		printf("We are already at the destination\n");
		return;
	}

	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));


	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;


	openList.insert(make_pair(0.0, make_pair(i, j)));


	while (!openList.empty()) {
		pPair p = *openList.begin();
		
		openList.erase(openList.begin());


		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;


		pthread_t n,s,e,w,ne,nw,se,sw;
		
		pthread_create(&n, NULL, north, NULL);
		pthread_create(&s, NULL, South, NULL);
		pthread_create(&w, NULL, west, NULL);
		pthread_create(&e, NULL, east, NULL);
		pthread_create(&ne, NULL, northEast, NULL);
		pthread_create(&nw, NULL, northWest, NULL);
		pthread_create(&se, NULL, southEast, NULL);
		pthread_create(&sw, NULL, southWest, NULL);
		
		pthread_join(n, NULL);
		pthread_join(s, NULL);
		pthread_join(w, NULL);
		pthread_join(e, NULL);
		pthread_join(ne, NULL);
		pthread_join(nw, NULL);
		pthread_join(se, NULL);
		pthread_join(sw, NULL);
		
		
	}
		
	if (foundDest == false)
//		printf("Failed to find the Destination Cell\n");

	return;
}

void* north(void *arg){

	
		if(foundDest){
			return NULL;
		}
		if (isValid(i - 1, j) == true) {
		
			if (isDestination(i - 1, j, dest) == true) {
	
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
//				printf("North The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return NULL;
			}

			else if (closedList[i - 1][j] == false
					&& isUnBlocked(grid, i - 1, j)
							== true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i - 1, j, dest);
				fNew = gNew + hNew;

				
				if (cellDetails[i - 1][j].f == FLT_MAX
					|| cellDetails[i - 1][j].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i - 1, j)));
					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}
}
void* South(void *arg){

		if(foundDest){
			return NULL;
		}
		if (isValid(i + 1, j) == true) {
	
			if (isDestination(i + 1, j, dest) == true) {

				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
//				printf("South The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return NULL;
			}
		
			else if (closedList[i + 1][j] == false
					&& isUnBlocked(grid, i + 1, j)
							== true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i + 1, j, dest);
				fNew = gNew + hNew;

		
				if (cellDetails[i + 1][j].f == FLT_MAX
					|| cellDetails[i + 1][j].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i + 1, j)));
			
					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}
}
	
void* east(void *arg){

		if (isValid(i, j + 1) == true) {
	
			if (isDestination(i, j + 1, dest) == true) {

				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
//				printf("The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return NULL;
			}

			else if (closedList[i][j + 1] == false
					&& isUnBlocked(grid, i, j + 1)
							== true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j + 1].f == FLT_MAX
					|| cellDetails[i][j + 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i, j + 1)));


					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}
}
void* west(void *arg){

		if (isValid(i, j - 1) == true) {
		
			if (isDestination(i, j - 1, dest) == true) {
			
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
//				printf("The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return NULL;
			}


			else if (closedList[i][j - 1] == false
					&& isUnBlocked(grid, i, j - 1)
							== true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j - 1, dest);
				fNew = gNew + hNew;

			
				if (cellDetails[i][j - 1].f == FLT_MAX
					|| cellDetails[i][j - 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i, j - 1)));

					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}
}

void* northEast(void *arg){
		if(foundDest){
			return NULL;
		}
		if (isValid(i - 1, j + 1) == true) {

			if (isDestination(i - 1, j + 1, dest) == true) {

				cellDetails[i - 1][j + 1].parent_i = i;
				cellDetails[i - 1][j + 1].parent_j = j;
//				printf("North East The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return NULL;
			}


			else if (closedList[i - 1][j + 1] == false
					&& isUnBlocked(grid, i - 1, j + 1)
							== true) {
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i - 1, j + 1, dest);
				fNew = gNew + hNew;

		
				if (cellDetails[i - 1][j + 1].f == FLT_MAX
					|| cellDetails[i - 1][j + 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i - 1, j + 1)));

	
					cellDetails[i - 1][j + 1].f = fNew;
					cellDetails[i - 1][j + 1].g = gNew;
					cellDetails[i - 1][j + 1].h = hNew;
					cellDetails[i - 1][j + 1].parent_i = i;
					cellDetails[i - 1][j + 1].parent_j = j;
				}
			}
		}
}

void* northWest(void *arg){
	
		if(foundDest){
			return NULL;
		}
		if (isValid(i - 1, j - 1) == true) {
	
			if (isDestination(i - 1, j - 1, dest) == true) {

				cellDetails[i - 1][j - 1].parent_i = i;
				cellDetails[i - 1][j - 1].parent_j = j;
//				printf("North West The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return NULL;
			}

			else if (closedList[i - 1][j - 1] == false
					&& isUnBlocked(grid, i - 1, j - 1)
							== true) {
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i - 1, j - 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i - 1][j - 1].f == FLT_MAX
					|| cellDetails[i - 1][j - 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i - 1, j - 1)));
		
					cellDetails[i - 1][j - 1].f = fNew;
					cellDetails[i - 1][j - 1].g = gNew;
					cellDetails[i - 1][j - 1].h = hNew;
					cellDetails[i - 1][j - 1].parent_i = i;
					cellDetails[i - 1][j - 1].parent_j = j;
				}
			}
		}
}

void* southEast(void *arg){

		if(foundDest){
			return NULL;
		}
		if (isValid(i + 1, j + 1) == true) {

			if (isDestination(i + 1, j + 1, dest) == true) {

				cellDetails[i + 1][j + 1].parent_i = i;
				cellDetails[i + 1][j + 1].parent_j = j;
//				printf("South East The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return NULL;
			}

	
			else if (closedList[i + 1][j + 1] == false
					&& isUnBlocked(grid, i + 1, j + 1)
							== true) {
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i + 1, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j + 1].f == FLT_MAX
					|| cellDetails[i + 1][j + 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i + 1, j + 1)));

					cellDetails[i + 1][j + 1].f = fNew;
					cellDetails[i + 1][j + 1].g = gNew;
					cellDetails[i + 1][j + 1].h = hNew;
					cellDetails[i + 1][j + 1].parent_i = i;
					cellDetails[i + 1][j + 1].parent_j = j;
				}
			}
		}
}
	
void* southWest(void *arg){

		if(foundDest){
			return NULL;
		}
		if (isValid(i + 1, j - 1) == true) {
			
			if (isDestination(i + 1, j - 1, dest) == true) {
	
				cellDetails[i + 1][j - 1].parent_i = i;
				cellDetails[i + 1][j - 1].parent_j = j;
//				printf("South West The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return NULL;
			}

		
			else if (closedList[i + 1][j - 1] == false
					&& isUnBlocked(grid, i + 1, j - 1)
							== true) {
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i + 1, j - 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j - 1].f == FLT_MAX
					|| cellDetails[i + 1][j - 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i + 1, j - 1)));

					cellDetails[i + 1][j - 1].f = fNew;
					cellDetails[i + 1][j - 1].g = gNew;
					cellDetails[i + 1][j - 1].h = hNew;
					cellDetails[i + 1][j - 1].parent_i = i;
					cellDetails[i + 1][j - 1].parent_j = j;
				}
			}
		}
	}
double timetaken(){
    double initial_s,final_s;
    double diff_s;
    initial_s= (double)initial.tv_sec*1000000 + (double)initial.tv_usec;
    final_s= (double)final.tv_sec*1000000 + (double)final.tv_usec;
    diff_s=(final_s-initial_s)/1000000;
    return diff_s;
}
int main()
{

	gettimeofday(&initial,NULL);
	aStarSearch(grid, src, dest);
    gettimeofday(&final,NULL);
    double diff=0;
    diff=timetaken();

    printf("Time taken in seconds is %f\n",diff);

	return (0);
}
				
