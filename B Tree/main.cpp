#include <iostream>
#include "BTree.h"

using namespace std;

int main() {
     BTree* btree = new BTree(2);
    btree->insert(1);
    btree->insert(3);
    btree->insert(7);
    btree->insert(10);
    btree->insert(11);
    btree->insert(13);
    btree->insert(14);
    btree->insert(15);
    btree->insert(18);
    btree->insert(16);
    btree->insert(19);
    btree->insert(24);
    btree->insert(25);
    btree->insert(26);
    btree->insert(21);
    btree->insert(4);
    btree->insert(5);
    btree->insert(20);
    btree->insert(22);
    btree->insert(2);
    btree->insert(17);
    btree->insert(12);
    btree->insert(6);
    btree->insert(27);
    btree->insert(39);
    btree->insert(84);
    btree->insert(47);
    btree->insert(68);
    btree->insert(94);
    btree->insert(43);
    btree->insert(45);
    btree->insert(67);
    btree->insert(69);
    btree->insert(9);
    btree->insert(58);
    btree->insert(35);
    btree->insert(64);
    btree->insert(31);
    btree->insert(30);
    btree->insert(45);
    btree->insert(37);
    btree->insert(36);
    btree->traverse();
    btree->remove(6);
    int valAux = btree->valueFound(btree->search(25), 25);
    cout<<valAux<<endl;
    btree->DrawBTree();
    cout<<get_uuid()<<endl;
    return 0;
}