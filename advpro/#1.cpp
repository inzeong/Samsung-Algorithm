#include<string.h>
#include<iostream>

struct Node {
    char _c;
    Node *next, *prev;
} node[90101];

Node *head, *tail, *rowStart[310], *nowPointer;
int charRow[27][310], cntRow[310];
int nowRow, nowCol, tot, H, W, minusChar[27];
int nodeCnt;

void add(Node *now, char c) {
    node[nodeCnt]._c = c;
    Node* tmp = &node[nodeCnt++];
    
    tmp->next = now->next; tmp->prev = now;
    now->next->prev = tmp; now->next = tmp;
}

int start;
void init(int _H, int _W, char mStr[]) {
    if(start == 0) {
        head = new Node(); tail = new Node();
    }
    start = 1;
    H = _H; W = _W;
    head->next = tail; tail->prev = head;
    
    nodeCnt = 0; nowRow = 1; 
    nowCol = 1; nowPointer = head; tot = 0;
    memset(charRow, 0, sizeof(charRow)); memset(cntRow, 0, sizeof(cntRow)); memset(minusChar, 0, sizeof(minusChar));
    rowStart[1] = head;
    Node *now = head;

    for(int i=1; mStr[i-1] != 0; i++) {
        int nowRow1 = (i-1) / W + 1;
        add(now, mStr[i-1]);
        charRow[mStr[i-1] - 'a' + 1][nowRow1]++;
        cntRow[nowRow1]++;
        tot++;
        now = now->next;
        if(i % W == 0) rowStart[nowRow1+1] = now;
    }

}

void insert(char mChar) {
    add(nowPointer, mChar);
    tot++;
    charRow[mChar - 'a' + 1][nowRow]++; cntRow[nowRow]++; minusChar[mChar - 'a' + 1]++;

    for(int i=nowRow; i<=H; i++) {
        if(cntRow[i] <= W) {
            if(cntRow[i] == W) {
                rowStart[i+1] = tail->prev;
            }
            break;
        }
        charRow[rowStart[i+1]->_c - 'a' + 1][i]--;
        cntRow[i]--;
        
        charRow[rowStart[i+1]->_c - 'a' + 1][i+1]++;
        cntRow[i+1]++;
        
        rowStart[i+1] = rowStart[i+1]->prev;
    }
    nowCol++;
    if(nowCol > W) {
		nowRow++; nowCol = 1; memset(minusChar, 0, sizeof(minusChar));
	}
    nowPointer = nowPointer->next;
}

char moveCursor(int mRow, int mCol) {
    memset(minusChar, 0, sizeof(minusChar));
    nowRow = mRow; nowCol = mCol;
    if( (mRow - 1) * W + mCol > tot ) {
        nowRow = (tot) / W + 1; nowCol = (tot) % W + 1;
    }
    nowPointer = rowStart[nowRow];
    for(int i=0; i< nowCol-1; i++) {
        if(nowPointer->next == tail) return '$';
        minusChar[nowPointer->next->_c - 'a' + 1]++;
        nowPointer = nowPointer->next;
    }
    if(nowPointer->next == tail) return '$';
    return nowPointer->next->_c;
}

int countCharacter(char mChar) {
    int ans = 0;
    for(int i=nowRow; cntRow[i] != 0; i++){
        ans += charRow[mChar - 'a' + 1][i];
    }
    return ans - minusChar[mChar - 'a' + 1];
}