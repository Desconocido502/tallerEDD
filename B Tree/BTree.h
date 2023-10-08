// Include header file
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "BTreeNode.h"
#include "generacionImg.h"

using namespace std;

class BTree{
public:
    BTreeNode *root;
    int MinDeg;
    vector<int> x; //save value's
    // Constructor
    BTree(int deg){
        this->root = nullptr;
        this->MinDeg = deg;
    }

    BTree(){
        this->root = nullptr;
        this->MinDeg = 0;
    }

    void traverse(){
        if (root != nullptr){
            root->traverse();
            cout<<endl;
        }
    }

    string DrawBTree(){
        generacionImg("ArbolB", root->toDot());
        string command = "ArbolB.png";
        string x = to_string(system(command.c_str()));
        //cout<<"x:"<<x<<endl;
        return x;
    }

    BTreeNode *search(int key){
        return ((root == nullptr) ? nullptr : root->search(key));
    }

    void insert(int key){
        int valAux = this->valueFound(this->search(key), key);
        if(valAux == key) return; //En caso de que vengan numeros repetidos no se insertan en el arbol

        if (root == nullptr){
            root = new BTreeNode(MinDeg, true);
            root->keys[0] = key;
            root->num = 1;
        }else{
            if (root->num == 2 * MinDeg - 1){
                BTreeNode *s = new BTreeNode(MinDeg, false);
                s->children[0] = root;
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0] < key){
                    i++;
                }
                s->children[i]->insertNotFull(key);
                root = s;
            }else{
                root->insertNotFull(key);
            }
        }
    }

    void remove(int key){
        if (root == nullptr){
            std::cout << "The tree is empty" << std::endl;
            return;
        }
        root->remove(key);
        if (root->num == 0){
            if (root->isLeaf){
                root = nullptr;
            }else{
                root = root->children[0];
                cout<<root<<endl;
            }
        }
    }

    int valueFound(BTreeNode* aux, int valueToBeSearch){
        if (aux == nullptr) return -1;
        for(int i =0; i < aux->num; i++){
            if(aux->keys[i] == valueToBeSearch){
                return aux->keys[i];
            }
        }
        return -1;
    }
};