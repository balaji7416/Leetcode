#include <bits/stdc++.h>
using namespace std;

/*
    Problem 225: Implement Stack using Queues
    data structure: stack,queue
    Time: push -> O(n), other operations -> O(1), Space: O(n)
*/

/*
    idea:
    simulate queue front as stack top, rotate the elements to
    make this happen
    --------------------------
    f | | | | | -----| | |
    --------------------------
    |
    top
*/

class MyStack
{
    queue<int> q;

public:
    MyStack()
    {
    }

    void push(int x)
    {
        q.push(x);
        for (int i = 0; i < q.size() - 1; i++)
        {
            int u = q.front();
            q.pop();
            q.push(u);
        }
    }

    int pop()
    {
        int u = q.front();
        q.pop();
        return u;
    }

    int top()
    {
        return q.front();
    }

    bool empty()
    {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */