#include <bits/stdc++.h>
#include "maze.h"

default_random_engine random(time(NULL));

Maze::Maze() {
    ;
}

int Maze::getMat(int x, int y)
{
    return this->tMat[x][y];
}

void Maze::setMat(int x, int y, bool val)
{
    this->tMat[x][y] = val;
}

vector<pair<int, int> >::iterator Maze::vpos(int p) {
    vector<pair<int, int> >::iterator ret = pQue.begin();
    while(p--) {
        ret++;
    }
    return ret;
}

bool Maze::findVec(pair<int, int> tmp) {
    bool ret = 0;
    for (vector<pair<int, int> >::iterator it = pQue.begin(); it != pQue.end(); it++) {
        if(tmp == *(it)) ret = 1;
    }
    return ret;
}

bool Maze::findSet(pair<int, int> tmp) {
    bool ret = 0;
    for (set<pair<int, int> >::iterator it = pFor.begin(); it != pFor.end(); it++) {
        if(tmp == *(it)) ret = 1;
    }
    return ret;
}

void Maze::mazeInit(int height, int width) {
    memset(tMat, 0, sizeof(tMat));
    height <<= 1;
    width <<= 1;
    for (int i = 1; i < height; i += 2) {
        for (int j = 1; j < width; j += 2) {
            tMat[i][j] = 1;
        }
    }
}

void Maze::pExpand(int x, int y, int height, int width) {
    pair<int, int> tp1 = make_pair(x - 1, y), tp2 = make_pair(x + 1, y), tp3 = make_pair(x, y - 1), tp4 = make_pair(x, y + 1);
    if (x > 1 && pFor.end() == pFor.find(tp1) && !findVec(tp1))
        pQue.push_back(tp1);
    if (y > 1 && pFor.end() == pFor.find(tp3) && !findVec(tp3))
        pQue.push_back(tp3);
    if (x < height && pFor.end() == pFor.find(tp2) && !findVec(tp2))
        pQue.push_back(tp2);
    if (y < width && pFor.end() == pFor.find(tp4) && !findVec(tp4)) 
        pQue.push_back(tp4);
}

void Maze::mazeGen(int height, int width, int stX, int stY) {
    mazeInit(height, width);
    
    pFor.clear();
    pQue.clear();
    pFor.insert(make_pair(stX, stY));
    pExpand(stX, stY, height, width);
    while (pQue.size()) {
        
        uniform_int_distribution<int> dis(0, pQue.size() - 1);
        int cur = dis(random), curX = pQue[cur].first, curY = pQue[cur].second;
        //cout << pQue.size() << cur << endl;
        if (pFor.end() != pFor.find(make_pair(curX - 1, curY))) {
            tMat[curX * 2 - 2][curY * 2 - 1] = 1;
        }
        else if (pFor.end() != pFor.find(make_pair(curX, curY - 1))) {
            tMat[curX * 2 - 1][curY * 2 - 2] = 1;
        }
        else if (pFor.end() != pFor.find(make_pair(curX + 1, curY))) {
            tMat[curX * 2][curY * 2 - 1] = 1;
        }
        else if (pFor.end() != pFor.find(make_pair(curX, curY + 1))) {
            tMat[curX * 2 - 1][curY * 2] = 1;
        }
        pFor.insert(pQue[cur]);
        pExpand(pQue[cur].first, pQue[cur].second, height, width);
        vector<pair<int, int> >::iterator iDel = vpos(cur);
        pQue.erase(iDel);
    }
}

void Maze::findPath(int stX, int stY, int edX, int edY) {
    memset(vMat, -1, sizeof(vMat));
    pFor.clear();
    while(!_open.empty())_open.pop();
    node stp =node(stX, stY, 0, abs(edX - stX) + abs(edY - stY));
    _open.push(stp);
    vMat[stX][stY] = stp._G;
    while (!_open.empty()) {
        node p = node();
        p = _open.top();
        int curX = p._x, curY = p._y;
        if (curX == edX && curY == edY) {
            while (curX != stX || curY != stY) {
                tMat[curX][curY] = tMat[stX][stY] = -1;
                if (vMat[curX - 1][curY] == vMat[curX][curY] - 1){
                    curX--;
                } else if (vMat[curX][curY - 1] == vMat[curX][curY] - 1){
                    curY--;
                } else if (vMat[curX + 1][curY] == vMat[curX][curY] - 1){
                    curX++;
                } else if (vMat[curX][curY + 1] == vMat[curX][curY] - 1){
                    curY++;
                }
            }
            break;
        }
        pFor.insert(make_pair(curX, curY));
        if ((tMat[curX - 1][curY] == 1 || tMat[curX - 1][curY] == -1) && pFor.end() == pFor.find(make_pair(curX - 1, curY))) {
            node tp = node(curX - 1, curY, p._G + 1, abs(edX - curX + 1) + abs(edY - curY));
            vMat[curX - 1][curY] = p._G + 1;
            _open.push(tp);
        }
        if ((tMat[curX][curY - 1] == 1 || tMat[curX][curY - 1] == -1) && pFor.end() == pFor.find(make_pair(curX, curY - 1))) {
            node tp = node(curX, curY - 1, p._G + 1, abs(edX - curX) + abs(edY - curY + 1));
            vMat[curX][curY - 1] = p._G + 1;
            _open.push(tp);
        }
        if ((tMat[curX + 1][curY] == 1 || tMat[curX + 1][curY] == -1) && pFor.end() == pFor.find(make_pair(curX + 1, curY))) {
            node tp = node(curX + 1, curY, p._G + 1, abs(edX - curX - 1) + abs(edY - curY));
            vMat[curX + 1][curY] = p._G + 1;
            _open.push(tp);
        }
        if ((tMat[curX][curY + 1] == 1 || tMat[curX][curY + 1] == -1) && pFor.end() == pFor.find(make_pair(curX, curY + 1))) {
            node tp = node(curX, curY + 1, p._G + 1, abs(edX - curX) + abs(edY - curY - 1));
            vMat[curX][curY + 1] = p._G + 1;
            _open.push(tp);
        }
        _open.pop();
    }  

}

