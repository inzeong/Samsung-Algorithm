# include <vector>
#define MAX_PLACE	50010
#define MAX_UID	    1010
#define MAX_VISIT	100
#define MAX_HASH	251731 
#define MAX_DIR		8

using namespace std;

struct Place {
	int r, c;		
	int pID;		
	int deleted;	
	int infected;	
} P[MAX_PLACE];

struct road {
	int r, c;
} A[MAX_DIR] = {
	-1, 0,
	-1, 1,
	0, 1, 
	1, 1,
	1, 0,
	1, -1,
	0 , -1,
	-1, -1
};

int nPlace;
Place* ht[MAX_HASH];
vector< int > v[MAX_UID];

int getHashVal(int r, int c) {
	return (r * 10001 + c) % MAX_HASH;
}

void init() {
	nPlace = 0;
	for (int i = 1; i < MAX_UID; i++)
		v[i].clear();
	for (int i = 0; i < MAX_HASH; i++) {
		ht[i] = nullptr;
	}
}

void setPlace(int r, int c, Place* curPlace) {
	int de = 0;
	int hval = getHashVal(r, c);
	Place* pPlace = ht[hval];
	if (pPlace == nullptr) {
		ht[hval] = curPlace;
		return;
	}
	while (de < MAX_HASH) {
		de++;
		pPlace = ht[(hval + de) % MAX_HASH];
		if (pPlace == nullptr) {
			ht[(hval + de) % MAX_HASH] = curPlace;
			return;
		}
	}	
}

Place* getPlace(int r, int c) {
	int de = 0;
	int hval = getHashVal(r, c);
	Place* pPlace = ht[hval];
	if (pPlace == nullptr)
        return pPlace;
	while (de < MAX_HASH) {
		if (pPlace->r == r && pPlace->c == c) {
			return pPlace;
		}
        
		de++;
		pPlace = ht[(hval + de) % MAX_HASH];
		if (pPlace == nullptr) return pPlace;
	}
	return nullptr;
}

void addPlace(int pID, int r, int c) {
	Place* pPlace = &P[nPlace];
	nPlace++;
    
    pPlace->c = c;
	pPlace->r = r;
	pPlace->deleted = 0;
	pPlace->infected = 0;
	pPlace->pID = nPlace;
	setPlace(r, c, pPlace);
}

void removePlace(int pID) {
	P[pID-1].deleted = 1;
}

Place* findNextPlace(Place* cur, int dir) {
	int cr = cur->r;
	int cc = cur->c;
	Place* curPlace = nullptr;
	cr += A[dir].r;
	cc += A[dir].c;
	while (cr >= 0 && cr < 10000 && cc >= 0 && cc < 10000) {
		curPlace = getPlace(cr, cc);
		if (curPlace != nullptr && curPlace->infected == 0 && curPlace->deleted == 0) return curPlace;
		cr += A[dir].r;
		cc += A[dir].c;
	}
	return nullptr;
}

void contactTracing(int uID, int visitNum, int moveInfo[], int visitList[]) {
	Place* curPlace = &P[moveInfo[0]-1];
	visitList[0] = curPlace->pID;
	v[uID].push_back(curPlace->pID);
	for (int i = 1; i < visitNum; i++) {
		curPlace = findNextPlace(curPlace, moveInfo[i]);
		if (curPlace == nullptr) {
			return;
		}
		visitList[i] = curPlace->pID;
		v[uID].push_back(curPlace->pID);
    }

	for (int i : v[uID]) {
		curPlace = &P[i - 1];
		curPlace->infected = 1;
	}
}

void disinfectPlaces(int uID) {
	Place* c = nullptr;
	for (int i : v[uID]) {
		c = &P[i-1];
		c->infected = 0;
	}
}