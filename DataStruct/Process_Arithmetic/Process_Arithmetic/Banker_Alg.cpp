#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct __TaskStruct
{
	const int _pid; // ����id
	const int _ppid; // ������id
	const int _priority; // �������ȼ�
	int _nice; // ���ȼ���������
	const int _s_time; // ����ִ����Ҫ��ʱ��
	int _r_time;// �����Ѿ����е��¼�
	
	// ��ʼ��
	__TaskStruct(int pid,int priority,int run_time) 
		:_pid(pid)
		,_priority(priority)
		,_ppid(1)
		,_nice(0)
		,_s_time(run_time)
		,_r_time(0)
	{}
};

typedef __TaskStruct PCB;
/***********ð������*************/
template<class Compare>
void Sort(vector<PCB*>& p,Compare com)
{
	int n = p.size();
	bool flag = false;
	for (size_t i = 0; i < n - 1; i++)
	{
		for (size_t j = 1; j < n - i; j++)
		{
			if (com(p[j], p[j - 1])) {
				swap(p[j - 1], p[j]);
				flag = true;
			}
		}
		if (!flag)
			break;
	}
}

class Process
{
public:
	Process():_time(0)
	{}

	void Push(PCB *p)
	{
		_p.push_back(p);
	}

	void HPFS()
	{
		cout << "HPFS:" << endl;
		struct Less
		{
			bool operator()(const PCB* l, const PCB* r)
			{
				return l->_priority < r->_priority;
			}
		};
		Sort(_p, Less());
		_Run();
	}

protected:
	// ��������ִ��
	void _Run()
	{
		for (size_t i = 0; i < _p.size(); ++i)
		{
			// ��ʼִ�У���ӡ��ǰִ�н��̵������Ϣ
			cout << "start! [" << "pid:" << _p[i]->_pid << " priorty:" <<
				_p[i]->_priority << " _s_time:" << _p[i]->_s_time << "]" << endl;

			// pid Ϊ i �Ľ��̿�ʼִ��
			while (_p[i]->_r_time < _p[i]->_s_time) {
				++_p[i]->_r_time;
				++_time;
				cout << "time:" << _time << " pid:" << _p[i]->_pid << " priorty:" <<
					_p[i]->_priority << " _r_time:" << _p[i]->_r_time << endl;
			}
			cout << "finish!"  << endl;

		}
	}

private:
	vector<PCB*> _p;
	int _time;
};

void test()
{
	PCB* p;
	size_t num = 0;//���̸���
	int priority = 0;//�������ȼ�
	int s_time = 0;//����ִ����ʱ��
	Process ps;
	cout << "Please input process number: ";
	cin >> num;
	for (size_t i = 0; i < num; ++i) {
		cin >> priority >> s_time;
		//	  pid    PR      s_time
		//   num = 3 
		// 1 7s
		// 2 3s
		// 3 10s
		ps.Push(new PCB(i, priority, s_time));
	}
	ps.HPFS();
}


int main()
{
	test();
	system("pause");
	return 0;
}