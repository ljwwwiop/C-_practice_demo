#pragma once
#include<queue>
using std::queue;

typedef struct {
	int x;
	int y;
}COORDINATE;

class FindPathBFS
{
private:
	// 用矩阵来表示一个图，m_chess二维数组，false表示通路，true表示不通
	bool **m_chess; 
	// 保存节点看是否被走过
	bool **m_visit; 
	// 每个访问过的节点的父节点
	COORDINATE **m_parent;
	// 地图大小
	COORDINATE m_size;
	void FindPath(COORDINATE begin_point,COORDINATE end_point);
	void GetQueue(COORDINATE end_point);
public:
	// 构造 析构 
	FindPathBFS();
	~FindPathBFS();
	void InitMap(bool **chess);
	void GetPath(COORDINATE begin_point, COORDINATE end_point);
	queue<COORDINATE> m_paths_queue;
};




