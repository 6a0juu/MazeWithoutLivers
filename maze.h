#ifndef MAZE_H
#define MAZE_H

#include <bits/stdc++.h>

using namespace std;

class Maze
{
public:
    //矩阵列表
    //bool mazeMat[2010][2010];
    //生成矩阵
    int tMat[1010][1010];
    Maze();
    int getMat(int x, int y);
    void setMat(int x, int y, bool val);
    void mazeGen(int height, int width, int stX, int stY);
    void findPath(int stX, int stY, int edX, int edY);

private:

    struct node {
        int _x, _y, _G, _H, _F;
        node(int x,int y, int G, int H): _x(x), _y(y), _G(G), _H(H), _F(G + H) {}
        node(): _x(0), _y(0), _G(0), _H(0), _F(0) {}
    };
    struct cmp {
        bool operator()(node n1, node n2) {
            return n1._F > n2._F;
        }
    };
    int vMat[1010][1010];
    priority_queue<node, vector<node>, cmp> _open;
    //邻墙列表
    vector<int> blockPos;
    vector<pair<int, int> > pQue;
    set<pair<int, int> > pFor;
    vector<pair<int, int> >::iterator vpos(int p);
    bool findVec(pair<int, int> tmp);
    bool findSet(pair<int, int> tmp);
    void mazeInit(int height, int width);
    void pExpand(int x, int y, int height, int width);
};

#endif
