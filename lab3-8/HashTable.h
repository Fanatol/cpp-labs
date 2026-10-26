#include <vector>

template <typename K, typename V>
class HashTable {
   private:
    struct Node {
        K key;
        V value;
        bool deleted;
        bool occupied;
        Node() : deleted(false), occupied(false) {}
        Node(const K& k, const V& v) : key(k), value(v), deleted(false), occupied(true) {}
    };
    int size;
    int count;
    std::vector<Node> table;
    int hash(const K& key) const { return key % size; }

   public:
    HashTable(int s) : table(s), size(s), count(0) {}
    ~HashTable() = default;

    bool find(const K& key, V& result) const {
        int index = hash(key);
        int i = 0;
        while (table[(index + i) % size].occupied or table[(index + i) % size].deleted) {
            int pos = (index + i) % size;
            if (table[pos].key == key and !table[pos].deleted) {
                result = table[pos].value;
                return true;
            }
            i++;
        }
        return false;
    }

    void insert(const K& key, const V& value) {
        int index = hash(key);
        int i = 0;
        int firstDel = -1;
        while (table[(index + i) % size].occupied or table[(index + i) % size].deleted) {
            int pos = (index + i) % size;
            if (table[pos].key == key) {
                table[pos].value = value;
                return;
            }
            if (table[pos].deleted and firstDel == -1) firstDel = pos;
            i++;
        }
        if (firstDel != -1) {
            table[firstDel].key = key;
            table[firstDel].value = value;
            table[firstDel].occupied = true;
            table[firstDel].deleted = false;
        } else {
            int pos = (index + i) % size;
            table[pos].key = key;
            table[pos].value = value;
            table[pos].occupied = true;
            table[pos].deleted = false;
        }
        count++;
    }

    void remove(const K& key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i) % size].occupied or table[(index + i) % size].deleted) {
            int pos = (index + i) % size;
            if (table[pos].key == key) {
                table[pos].deleted = true;
                table[pos].occupied = false;
                count--;
                return;
            }
            i++;
        }
    }
};
