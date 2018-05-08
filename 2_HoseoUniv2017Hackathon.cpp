#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

const int magicNum = 100000000; // 갈 수 없는 값.
int matrix[200][200];
int dimension;

int getMaxMoving(int* path, int ab, int a, int aa, int bb, int b, int ba) {
	int max = -1;

	if (max < matrix[path[ab]][path[a]])
		max = matrix[path[ab]][path[a]];

	if (max < matrix[path[a]][path[aa]])
		max = matrix[path[a]][path[aa]];

	if (max < matrix[path[bb]][path[b]])
		max = matrix[path[bb]][path[b]];

	if (max < matrix[path[b]][path[ba]])
		max = matrix[path[b]][path[ba]];

	return max;
}

int calcMaxMoving(int* path) {
	int max = -1;
	for (int i = 0; i < dimension; i++)
		if (max < matrix[path[i]][path[i + 1]])
			max = matrix[path[i]][path[i + 1]];


	return max;
}

int** runCode(int startPosition)
{
	bool isVisited[200] = { false }; // 방문했는지 여부
	int** ret = new int*[2];
	int* path = new int[dimension + 1];
	int* minVal = new int;
	ret[0] = minVal;
	ret[1] = path;

	int pathIdx = 0;
	path[pathIdx++] = startPosition; // 처음 시작 도시
									 // cout << "경로 : "<< startPosition << "->";
	int x, y, curMax = magicNum;
	x = startPosition;
	isVisited[startPosition] = true;
	for (int i = 0; i < dimension - 1; i++) {
		for (int j = 0; j < dimension; j++) {
			if (isVisited[j] == false) {
				if (curMax >= matrix[x][j]) {
					curMax = matrix[x][j];
					y = j;
				}
			}
		}

		path[pathIdx++] = y;

		isVisited[y] = true;
		x = y;

		curMax = magicNum;
	}

	path[pathIdx++] = startPosition;
	bool isChanged = true;
	while (isChanged) {
		isChanged = false;
		for (int i = 1; i < dimension; i++) {
			for (int j = 1; j < dimension; j++) {
				if (abs(i - j) < 3)
					continue;
				if (getMaxMoving(path, i - 1, i, i + 1, j - 1, j, j + 1) > getMaxMoving(path, i - 1, j, i + 1, j - 1, i, j + 1)) {
					int temp = path[i];
					path[i] = path[j];
					path[j] = temp;
					isChanged = true;
				}

			}
		}
	}




	* minVal = calcMaxMoving(path);
	return ret;
}

int main() {
	bool isDebug = false;
	::clock_t t1 = ::clock();
	::clock_t t2;

	char tmp[100];
	ifstream fin;
	fin.open("ftv170.dat", ios::in);

	fin.getline(tmp, 100);
	fin.getline(tmp, 100);
	fin.getline(tmp, 100);


	fin >> tmp;
	fin >> dimension; // DIMENSION

					  // cout << dimension;

	fin.getline(tmp, 100);
	fin.getline(tmp, 100);
	fin.getline(tmp, 100);

	fin >> tmp;
	for (int x = 0; x < dimension; x++) {
		for (int y = 0; y < dimension; y++) {
			fin >> matrix[x][y];
		}
	}
	int bestStartingNode = 0;
	int min = magicNum;
	for (int i = 0; i < dimension; i++) {
		int** ret = runCode(i);
		if (isDebug)
			cout << i << "Node, " << "Cost = " << *ret[0] << '\n';
		if (*ret[0] < min) {
			min = *ret[0];
			bestStartingNode = i;
		}
		for (int j = 0; j < dimension; j++) {
			if (isDebug)
				cout << (ret[1][j]) << "->";
		}
		if (isDebug)
			cout << (ret[1][dimension]) << "\n\n";

		delete ret[0];
		delete[] ret[1];
		delete[] ret;
	}

	t2 = ::clock();
	cout << "모든 노드의 최소 Cost = " << min << endl;
	cout << "최소 Cost의 노드번호 = " << bestStartingNode << endl;
	cout << "계산 시간 = " << (float)t2 - (float)t1 << " ms" << endl;
}