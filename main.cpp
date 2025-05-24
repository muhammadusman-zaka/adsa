#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

// I could use the actual strings to represent the 'status'
// But string comparisons are expensive and hash tables need to as fast as possible
// So I will be using enumeration
enum Status {NEVER_USED, OCCUPIED, TOMBSTONE};

// Creating a struct to represent each element in the hashtable
struct Node
{
    std::string key;
    Status status;

    Node() : key(""), status(NEVER_USED) {}
};

// Class Implementation of HashTable
class HashTable{
    private:
        std::vector<Node> table;

        // Hashing function
        int hash(const std::string& key){
            return key.back() - 'a';
        }

        // Searching function
        int search(const std::string& key){
            int index = hash(key);
            int startIndex = index;

            while (table[index].status != NEVER_USED)
            {
                if (table[index].status == OCCUPIED && table[index].key == key)
                {
                    return index;
                }
                index = (index + 1) % 26;
                
                // This means we have come back around to a full circle
                if (index == startIndex)
                {
                    break;
                }
            }
            return -1;
        }

        // Function to find the index at which to insert a new key
        int findInsertionIndex(const std::string& key){
            int index = hash(key);
            int startIndex = index;

            while (table[index].status == OCCUPIED && table[index].key != key)
            {
                index = (index + 1) % 26;
                // Table is full
                if (index == startIndex)
                {
                    return -1;
                }
                
            }
            return index;
        }

    public:
        // Constructor
        HashTable() : table(26) {}

        void insert(const std::string& key){
            // Checks if key already exists
            if (search(key) != -1)
            {
                return;
            }
            
            int index = findInsertionIndex(key);
            if (index != -1)
            {
                table[index].key = key;
                table[index].status = OCCUPIED;
            }
        }

        void remove(const std::string& key){
            int index = search(key);
            if(index != -1){
                table[index].status = TOMBSTONE;
            }
        }

        void print(){
            for (int i = 0; i < 26; i++)
            {
                if (table[i].status == OCCUPIED)
                {
                    std::cout << table[i].key << " "; 
                }
                
            }
            std::cout << std::endl;
        }

};


int main(){
    HashTable hashTable;
    std::string input;
    
    std::getline(std::cin, input);
    std::stringstream ss(input);

    std::string word;

    while (ss >> word)
    {
        if (word[0] == 'A')
        {
            hashTable.insert(word.substr(1));
        }

        else if (word[0] == 'D')
        {
            hashTable.remove(word.substr(1));
        }
    }

    hashTable.print();
    
    return 0;
}