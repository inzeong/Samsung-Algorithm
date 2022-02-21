#include <algorithm>
#include <bitset>
#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 50000, LIM = 11, PARTICLE = 100;

int boxL, boxR;
int X[MAX], Y[MAX], Z[MAX];
int VX[MAX], VY[MAX], VZ[MAX];

int EX[MAX];
int XYZ[LIM][LIM][LIM][PARTICLE];
int sz[LIM][LIM][LIM];
int in[MAX], temp[MAX];
int insz, tempsz;

void init(int L, int R) {
	for (int x = 0; x < 10; ++x) for (int y = 0; y < 10; ++y) for (int z = 0; z < 10; ++z) sz[x][y][z] = 0;
	insz = tempsz = 0;
	memset(EX, 0, sizeof(EX));
	boxL = L;
	boxR = R;
}

void insertParticle(int mID, int mPx, int mPy, int mPz, int mVx, int mVy, int mVz) {
	EX[mID] = 1;
	X[mID] = mPx + boxL;
	Y[mID] = mPy + boxL;
	Z[mID] = mPz + boxL;
    
	VX[mID] = mVx;
	VY[mID] = mVy;
	VZ[mID] = mVz;
	in[insz++] = mID;
    
	int xn = min(9, X[mID] / (boxL / 5));
	int yn = min(9, Y[mID] / (boxL / 5));
	int zn = min(9, Z[mID] / (boxL / 5));
    
	XYZ[xn][yn][zn][sz[xn][yn][zn]++] = mID;
}

void removeParticle(int mID) {
	EX[mID] = 0;
}

int findNearParticle(int mID) {
	int ans = 0;

	int xn = min(9, X[mID] / (boxL / 5));
	int yn = min(9, Y[mID] / (boxL / 5));
	int zn = min(9, Z[mID] / (boxL / 5));

	for (int x = max(0, xn - 1); x <= min(9, xn + 1); ++x) {
		for (int y = max(0, yn - 1); y <= min(9, yn + 1); ++y) {
			for (int z = max(0, zn - 1); z <= min(9, zn + 1); ++z) {
				for (int i = 0; i < sz[x][y][z]; ++i) {
					int n = XYZ[x][y][z][i];
                    
					if (!EX[n]) continue;
					int xd = abs(X[mID] - X[n]);
					int yd = abs(Y[mID] - Y[n]);
					int zd = abs(Z[mID] - Z[n]);
                    
					if (xd * xd + yd * yd + zd * zd <= boxR * boxR){
                        ans += n;
                    }
				}
			}
		}
	}
	return ans - mID;
}

void go(int mTick) {
	tempsz = 0;
	for (int x = 0; x < 10; ++x) for (int y = 0; y < 10; ++y) for (int z = 0; z < 10; ++z) sz[x][y][z] = 0;
	for (int i = 0; i < insz; ++i) {
		int mID = in[i];
		if (!EX[mID]) continue;
		X[mID] += VX[mID] * mTick + 40 * boxL;
		Y[mID] += VY[mID] * mTick + 40 * boxL;
		Z[mID] += VZ[mID] * mTick + 40 * boxL;


		X[mID] %= 4 * boxL;
		Y[mID] %= 4 * boxL;
		Z[mID] %= 4 * boxL;

		if (X[mID] > 2 * boxL) {
			X[mID] = 4 * boxL - X[mID];
			VX[mID] *= -1;
		}
        
		if (Y[mID] > 2 * boxL) {
			Y[mID] = 4 * boxL - Y[mID];
			VY[mID] *= -1;
		}
        
		if (Z[mID] > 2 * boxL) {
			Z[mID] = 4 * boxL - Z[mID];
			VZ[mID] *= -1;
		}

		int xn = min(9, X[mID] / (boxL / 5));
		int yn = min(9, Y[mID] / (boxL / 5));
		int zn = min(9, Z[mID] / (boxL / 5));
        
		XYZ[xn][yn][zn][sz[xn][yn][zn]++] = mID;
		temp[tempsz++] = mID;
	}
	swap(insz, tempsz);
	swap(tempsz, insz);
}