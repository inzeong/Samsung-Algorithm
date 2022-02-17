#include <algorithm>
#include <string.h> 
#include <queue>
#include <vector>
#include <functional>
#include <unordered_map>

#define N 500
using namespace std;

struct Product {
    int pId, lineId;
    int eId, nTime;
};

struct Request {
    int time;
    Product p;
    bool operator<(const Request& y) const {
        return time > y.time;
    }
};


int n, m;
int now;

bool lineUse[N], eUse[N];
queue<Product> LQ[N];

priority_queue<Request> TQ;

int casheLine[N];
unordered_map<int, int> casheProduct;

void init(int _n, int _m) {
    n = _n; 
    m = _m;
    now = 0;
    
    for (register int i = 0; i < n; i++) {
        while (!LQ[i].empty()) LQ[i].pop();
    }
    
    memset(lineUse, false, n);
    memset(eUse, false, m);
    
    while (!TQ.empty()) TQ.pop();
    casheProduct.clear();
}

void flow(int t) {
    while (!TQ.empty() && TQ.top().time <= t) {
        now = TQ.top().time;
        while( TQ.top().time == now && TQ.empty() == false) {
            register Product pp = TQ.top().p; TQ.pop();

            if (pp.pId < 0) continue;
            lineUse[pp.lineId] = false;
            eUse[pp.eId] = false;
            casheProduct[pp.pId] = 3;
        }

        for (register int i = 0; i < n; i++) {
            if (lineUse[i] == false && !LQ[i].empty()) {
                register Product pp = LQ[i].front();

                if (eUse[pp.eId] == false) {
                    lineUse[i] = true;
                    casheLine[i] = pp.pId;

                    eUse[pp.eId] = true;
                    casheProduct[pp.pId] = 2;

                    TQ.push({ now + pp.nTime, pp });
                    LQ[i].pop();
                }
            }
        }
    }
}

int request(int tStamp, int pId, int mLine, int eId, int mTime) {
    flow(tStamp - 1);

    LQ[mLine].push({ pId, mLine, eId, mTime });
    TQ.push({ tStamp, { -1 } });
    casheProduct[pId] = 1;
    
    now = tStamp;
    flow(tStamp);
    return lineUse[mLine] ? casheLine[mLine] : -1;
}

int status(int tStamp, int pId) {
    flow(tStamp);
    return casheProduct[pId];
}