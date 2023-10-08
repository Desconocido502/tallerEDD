#include <iostream>
#include "BTree.h"

using namespace std;

int main() {
     BTree* btree = new BTree(2);
    btree->insert(8);
    btree->insert(9);
    btree->insert(10);
    btree->insert(11);
    btree->insert(15);
    btree->insert(20);
    btree->insert(17);
    int valAux = btree->valueFound(btree->search(25), 25);
    cout<<valAux<<endl;
    btree->DrawBTree();
    cout<<get_uuid()<<endl;
    return 0;
}