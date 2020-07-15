#pragma once
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <queue>
using namespace std;

template<class V, class W>
struct Edge
{
	size_t _src;
	size_t _dst;
	W _weight;
	Edge* _next;

	Edge(size_t src, size_t dst, W w)
		:_src(src)
		, _dst(dst)
		, _weight(w)
		, _next(NULL)
	{}
};

template<class V, class W>
class GraphLink
{
	typedef Edge<V, W> Edge;
public:
	GraphLink(V* vertex, size_t size, bool isdirect = false)
		:_vertex(vertex, vertex + size)
		, _isdirect(isdirect)
	{
		_link_table.resize(size);
	}

	~GraphLink()
	{
		for (int i = 0; i < _link_table.size(); ++i)
		{
			Edge* cur = _link_table[i];
			while (cur)
			{
				Edge* del = cur;
				cur = cur->_next;
				delete del;
			}
		}
	}

	void AddEdge(const V& src, const V& dst, const W& w)
	{
		size_t index1 = GetIndex(src);
		size_t index2 = GetIndex(dst);
		if (_isdirect == false) //无向图
		{
			_AddEdge(index1, index2, w);
			_AddEdge(index2, index1, w);
		}
		else					//有向图
		{
			_AddEdge(index1, index2, w);
		}
	}

	void BFS(const V& src)
	{
		size_t index = GetIndex(src);
		vector<bool> visited(_vertex.size(), false);
		queue<size_t> q;
		q.push(index);
		while (!q.empty())
		{
			size_t front = q.front();
			q.pop();
			cout << _vertex[front].c_str() << "->";
			visited[front] = true;
			Edge* cur = _link_table[front];
			while (cur)
			{
				if (visited[cur->_dst] == false)
				{
					q.push(cur->_dst);
					visited[cur->_dst] = true;
				}
				cur = cur->_next;
			}
		}
		cout << endl;
		cout << "this is BFS" << endl;
	}

	void DFS(const V& src)
	{
		vector<bool> visited(_vertex.size(), false);
		size_t index = GetIndex(src);
		_DFS(index, visited);

		//有可能不是一个连通图
		for (int i = 0; i < visited.size(); ++i)
		{
			if (visited[i] == false)
				_DFS(i, visited);
		}
		cout << endl;
		cout << "this is DFS" << endl;
	}
protected:
	void _DFS(size_t src, vector<bool>& visited)
	{
		Edge* cur = _link_table[src];
		cout << _vertex[src] << "->";
		visited[src] = true;
		while (cur)
		{
			if (visited[cur->_dst] == false)
				_DFS(cur->_dst, visited);

			cur = cur->_next;
		}
	}

	size_t GetIndex(const V& src)
	{
		for (int i = 0; i < _vertex.size(); ++i)
		{
			if (_vertex[i] == src)
				return i;
		}
		assert(false);
		return -1;
	}

	void _AddEdge(size_t src, size_t dst, const W& w)
	{
		Edge* cur = new Edge(src, dst, w);

		//进行一次头插
		cur->_next = _link_table[src];
		_link_table[src] = cur;
	}
private:
	vector<V> _vertex;
	vector<Edge*> _link_table;
	bool _isdirect;
};


void TestGraphLink()
{
	string strs[] = { "China", "Japan", "Korea", "Russia","USA" };
	GraphLink<string, int> gl(strs, sizeof(strs) / sizeof(strs[0]));

	gl.AddEdge("China", "Japan", 100);
	gl.AddEdge("China", "Korea", 200);
	gl.AddEdge("China", "Russia", 300);
	gl.AddEdge("Japan", "Korea", 150);
	gl.AddEdge("Russia", "Japan", 400);
	gl.AddEdge("USA", "China", 250);

	gl.BFS("China");
	gl.DFS("USA");
}


