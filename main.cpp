#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* prev;
   Node* next;
   int key;
   int value;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{

public:
   map<int,Node*> mp; //map the key to the node in the linked list
   unsigned int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function
   virtual ~Cache(){}

};
class LRUCache : public Cache{
public:
    LRUCache(int c){
        cp = (unsigned int)c;
    }
    void set(int k, int v){
        map<int,Node*>::iterator it = mp.find(k);
        if(it != mp.end()){
            Node* fnd = it->second;
            if(fnd != head){
                if(fnd == tail){
                    tail->prev->next = NULL;
                    tail = tail->prev;
                }
                else{
                    fnd->prev->next = fnd->next;
                    fnd->next->prev = fnd->prev;
                }
                fnd->prev = NULL;
                fnd->next = head;
                head->prev = fnd;
                head = fnd;
            }
            fnd->value = v;
        }
        else{
            if(mp.size() == cp){
                int tail_key = tail->key;
                tail = mp[tail_key]->prev;
                delete mp[tail_key];
                mp.erase(tail_key);
                if(tail != NULL){
                    tail->next = NULL;
                }
                else{
                    head = NULL;
                }
            }
            Node* a = new Node(NULL, head, k, v);
            if(mp.size() == 0){
                tail = a;
            }
            else{
                head->prev = a;
            }
            head = a;
            mp[k] = a;
        }
    }
    int get(int a) {
        map<int, Node *>::iterator it = mp.find(a);
        if(it == mp.end()){
            return(-1);
        }
        else{
            return(it->second->value);
        }
    }
};

int main() {
   int n, capacity,i;
   ifstream mf;
   string file_name = "example";
   mf.open(file_name + ".txt");
   ofstream mfo;
   mfo.open(file_name + "_res.txt");
   //cin >> n >> capacity;
   mf >> n >> capacity;
   mfo << n << "   " << capacity << endl;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      //cin >> command;
      mf >> command;
      if(command == "get") {
         int key;
         //cin >> key;
         mf >> key;
         cout << i << "  get key " << key << "  " << l.get(key) << "   size " << l.mp.size() << endl;
         mfo << i << "  get key " << key << "  " << l.get(key) << "   size " << l.mp.size() << endl;
      }
      else if(command == "set") {
         int key, value;
         //cin >> key >> value;
         mf >> key >> value;
         l.set(key,value);
         cout << i << "  set key " << key << "  " << value << endl;
         mfo << i << "  set key " << key << "  " << value << endl;
      }
   }
   mf.close();
   mfo.close();
   return 0;
}
