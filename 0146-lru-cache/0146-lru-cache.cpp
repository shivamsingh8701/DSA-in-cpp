
class LRUCache {
public:

    class Node {
    public:
        int key, val;
        Node* prev;
        Node* next;

        Node(int k, int v) {
            key = k;
            val = v;
            prev = next = nullptr;
        }
    };

    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);

    unordered_map<int, Node*> m;
    int limit;

    // Delete a node from the DLL
    void delnode(Node* oldnode) {
        Node* oldprev = oldnode->prev;
        Node* oldnext = oldnode->next;

        oldprev->next = oldnext;
        oldnext->prev = oldprev;
    }

    // Add node immediately after head
    void addnode(Node* newnode) {
        Node* oldnext = head->next;

        head->next = newnode;
        oldnext->prev = newnode;

        newnode->next = oldnext;
        newnode->prev = head;
    }

    LRUCache(int capacity) {
        limit = capacity;

        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {

        if (m.find(key) == m.end()) {
            return -1;
        }

        Node* ansNode = m[key];
        int ans = ansNode->val;

        delnode(ansNode);
        addnode(ansNode);

        return ans;
    }

    void put(int key, int value) {

        // If key already exists, remove old node
        if (m.find(key) != m.end()) {
            Node* oldNode = m[key];

            delnode(oldNode);
            m.erase(key);
            delete oldNode;
        }

        // If capacity is full, remove LRU node
        if (m.size() == limit) {
            Node* lru = tail->prev;

            m.erase(lru->key);
            delnode(lru);
            delete lru;
        }

        // Insert new node at front
        Node* newnode = new Node(key, value);

        addnode(newnode);
        m[key] = newnode;
    }
};


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */