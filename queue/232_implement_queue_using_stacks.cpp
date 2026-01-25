#include <bits/stdc++.h>
using namespace std;

/*
    Problem 232: Implement Queue using Stacks
    data structure: stack,queue
    Time: O(1), Space: O(n)
*/

/*
    idea: pop from one stack and push to other stack => reverse of stack => queue
    use 2 stacks
    1. stack in -> push operations
       stack out -> pop operations and top

*/

class MyQueue
{
    stack<int> in, out;

public:
    MyQueue()
    {
    }

    void push(int x)
    {
        in.push(x);
    }

    int pop()
    {
        if (out.empty())
        {
            while (!in.empty())
            {
                out.push(in.top());
                in.pop();
            }
        }
        int u = out.top();
        out.pop();
        return u;
    }
    int peek()
    {
        if (out.empty())
        {
            while (!in.empty())
            {
                out.push(in.top());
                in.pop();
            }
        }
        return out.top();
    }

    bool empty()
    {
        return in.empty() && out.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */