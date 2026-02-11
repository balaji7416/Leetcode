#include <bits/stdc++.h>
using namespace std;

/*
    Problem 146: LRU Cache
    Pattern: Hashmap + Doubly Linked List
    Time: O(1), Space: O(n)
*/

/*
LRU Cache – Implementation Logic (HashMap + Doubly Linked List)

1. Maintain:
   - A HashMap: key -> pointer to node (for O(1) access)
   - A Doubly Linked List to track usage order
     • Front = Most Recently Used (MRU)
     • Back = Least Recently Used (LRU)

2. On get(key):
   - If key not in map → return -1
   - Else:
       • Locate node using map
       • Move that node to the front (mark as recently used)
       • Return its value

3. On put(key, value):
   - If key already exists:
       • Update its value
       • Move node to the front
   - Else:
       • If cache is at capacity:
            - Remove node at the back (LRU)
            - Remove its key from the map
       • Create new node
       • Insert it at the front (MRU)
       • Add key -> node to map

Core Idea:
- HashMap provides fast lookup.
- Doubly linked list maintains usage order.
- Every access refreshes recency.
- When full, evict the least recently used item.
*/

struct Node
{
    int key, val;
    struct Node *next;
    struct Node *prev;
    Node(int key, int val) : key(key), val(val), next(nullptr), prev(nullptr) {}
};
class LRUCache
{
private:
    unordered_map<int, Node *> mp;
    Node *head;
    Node *tail;
    int currSize;
    int maxSize;

public:
    LRUCache(int capacity)
    {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
        currSize = 0;
        maxSize = capacity;
    }

    int get(int key)
    {
        // if key found
        if (mp.count(key))
        {
            Node *temp = mp[key];

            // move node to the front if it's not already at front
            if (temp->prev != head)
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                temp->prev = head;
                temp->next = head->next;
                head->next->prev = temp;
                head->next = temp;
            }

            return temp->val;
        }

        // if key not found
        return -1;
    }

    void put(int key, int value)
    {
        // if key already exist
        if (mp.count(key))
        {
            Node *temp = mp[key];
            temp->val = value;

            // move node to the front if it's already not at front
            if (temp->prev != head)
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                temp->prev = head;
                temp->next = head->next;
                head->next->prev = temp;
                head->next = temp;
            }
            return;
        }

        // remove the node from back (LRU) if capacity is already reached
        if (currSize == maxSize)
        {
            Node *temp = tail->prev;
            int key = temp->key;
            temp->prev->next = tail;
            tail->prev = temp->prev;
            delete temp;
            mp.erase(key);
            currSize--;
        }
        Node *newnode = new Node(key, value);

        // insert newnode at front
        newnode->next = head->next;
        newnode->prev = head;
        head->next->prev = newnode;
        head->next = newnode;
        mp[key] = newnode;
        currSize++;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */