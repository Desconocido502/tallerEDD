#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <sstream>

using namespace std;
string get_uuid();

class BTreeNode{
private:
    int count;
    string buff;
    string id = "";
public:
    vector<int> keys;               //llaves de nodos
    int MinDeg;                     //Grado minimo de un nodo en el arbol B
    vector<BTreeNode *> children;   //Nodo hijo
    int num;                        //numero de llaves de nodos
    bool isLeaf;                    // Verdadero cuando es un nodo hoja

    //Constructor
    BTreeNode(int deg, bool isLeaf){
        this->MinDeg = deg;
        this->isLeaf = isLeaf;
        this->keys = vector<int>(2 * this->MinDeg - 1);
        this->children = vector<BTreeNode *> (2 * this->MinDeg);
        this->num = 0;
        this->id = get_uuid();
    }

    int findkey(int key){
        int idx = 0;
        while(idx < num && keys[idx] < key){
            ++idx;
        }
        return idx;
    }

    void remove(int key){
        int idx = findkey(key);
        if(idx < num && keys[idx] == key){
            if(isLeaf){
                removeFromLeaf(idx);
            }else{
                removeFromNonLeaf(idx);
            }
        }else{
            if(isLeaf){
                // If the node is a leaf node, then the node is not in the B tree
                printf("The key %d is does not exist in the tree\n", key);
                return;
            }
            bool flag = idx == num;
            
            if(children[idx]->num < MinDeg){
                fill(idx);
            }

            if(flag && idx > num){
                children[idx - 1]->remove(key);
            }else{
                children[idx]->remove(key);
            }
        }
    }

    void removeFromLeaf(int idx){
        for(int i = idx + 1; i < num; i++){
            keys[i - 1] = keys[i];
        }
        num--;
    }

    void removeFromNonLeaf(int idx){
        int key = keys[idx];

        if(children[idx]->num >= MinDeg){
            int pred = getPred(idx);
            keys[idx] = pred;
            children[idx]->remove(pred);
        }else if(children[idx + 1]->num >= MinDeg){
            int succ = getSucc(idx);
            keys[idx] = succ;
            children[idx + 1]->remove(succ);
        }else{
            merge(idx);
            children[idx]->remove(key);
        }
    }

    int getPred(int idx){
        BTreeNode *cur = children[idx];
        while(!cur->isLeaf){
            cur = cur->children[cur->num];
        }
        return cur->keys[cur->num - 1];
    }

    int getSucc(int idx){
        BTreeNode *cur = children[idx + 1];
        while (!cur->isLeaf){
            cur = cur->children[0];
        }
        return cur->keys[0];
    }

    void fill(int idx){
        if (idx != 0 && children[idx - 1]->num >= MinDeg){
            borrowFromPrev(idx);
        }else if (idx != num && children[idx + 1]->num >= MinDeg){
            borrowFromNext(idx);
        }else{
            if (idx != num){
                merge(idx);
            }else{
                merge(idx - 1);
            }
        }
    }

    void borrowFromPrev(int idx){
        BTreeNode *child = children[idx];
        BTreeNode *sibling = children[idx - 1];

        for(int i = child->num -1; i >= 0; --i){
            child->keys[i + 1] = child->keys[i];
        }

        if(!child->isLeaf){
            for(int i = child->num; i >= 0; --i){
                child->children[i + 1] = child->children[i];
            }
        }

        child->keys[0] = keys[idx - 1];
        if(!child->isLeaf){
            child->children[0] = sibling->children[sibling->num];
        }
        keys[idx - 1] = sibling->keys[sibling->num - 1];
        child->num += 1;
        sibling->num -= 1;
    }

    void borrowFromNext(int idx){
        BTreeNode *child = children[idx];
        BTreeNode *sibling = children[idx + 1];
        child->keys[child->num] = keys[idx];

        if(!child->isLeaf){
            child->children[child->num + 1] = sibling->children[0];
        }

        keys[idx] = sibling->keys[0];

        for(int i = 1; i < sibling->num; ++i){
            sibling->keys[i - 1] = sibling->keys[i];
        }

        if(!sibling->isLeaf){
            for(int i = 1; i <= sibling->num; ++i){
                sibling->children[i - 1] = sibling->children[i];
            }
        }
        child->num += 1;
        sibling->num -= 1;
    }

    void merge(int idx){
        BTreeNode *child = children[idx];
        BTreeNode *sibling = children[idx + 1];

        child->keys[MinDeg - 1] = keys[idx];

        for(int i = 0; i < sibling->num; ++i){
            child->keys[i + MinDeg] = sibling->keys[i];
        }

        if (!child->isLeaf){
            for(int i = 0; i <= sibling->num; ++i){
                child->children[i + MinDeg] = sibling->children[i];
            }
        }

        for (int i = idx + 1; i < num; ++i){
            keys[i - 1] = keys[i];
        }

        for (int i = idx + 2; i <= num; ++i){
            children[i - 1] = children[i];
        }

        child->num += sibling->num + 1;
        num--;
    }

    void insertNotFull(int key){
        int i = num -1;

        if(isLeaf){
            while (i >= 0 && keys[i] > key){
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
            num = num + 1;
        }else{
            while (i >= 0 && keys[i] > key){
               i--;
            }
            if (children[i + 1]->num == 2 * MinDeg - 1){
                splitChild(i + 1, children[i + 1]);
                if(keys[i + 1] < key){
                    i++;
                }
            }
            children[i + 1]->insertNotFull(key);
        }
    }

    void splitChild(int i, BTreeNode *&y){
        BTreeNode *z = new BTreeNode(y->MinDeg, y->isLeaf);
        z->num = MinDeg - 1;

        for (int j = 0; j < MinDeg - 1; j++){
            z->keys[j] = y->keys[j + MinDeg];
        }

        if (!y->isLeaf){
            for (int j = 0; j < MinDeg; j++){
                 z->children[j] = y->children[j + MinDeg];
            }
        }

        y->num = MinDeg - 1;
        
        for (int j = num; j >= i + 1; j--){
            children[j + 1] = children[j];
        }

        children[i + 1] = z;
        
        for (int j = num - 1; j >= i; j--){
            keys[j + 1] = keys[j];
        }

        keys[i] = y->keys[MinDeg - 1];
        num = num + 1;
    }

    void traverse(){
        int i;
        for (i = 0; i < num; i++){
            if (!isLeaf){
                children[i]->traverse();
            }
            printf(" %d", keys[i]);
        }
        if (!isLeaf){
            children[i]->traverse();
        }
    }

    BTreeNode *search(int key){
        int i = 0;
        while (i < num && key > keys[i]){
            i++;
        }
        if (keys[i] == key){
            return this;
        }
        if (isLeaf){
            return nullptr;
        }
        return children[i]->search(key);
    }

private:
    void Writer(){
        this->buff = "";
    }

    void Counter(){
        this->count = 0;
    }

    int add(){
        return this->count++;
    }

    void write(std::string str){
        this->buff += str;
    }

    void writeln(std::string str){
        this->write(str + "\n");
    }

public:
    std::string toDot(){
        Writer();
        Counter();
        return "digraph g {\nlabel=\"B Tree\";\nrankdir=TB; \nnode [shape=record, height=.1, color=blue ,style=\"rounded,filled\", fillcolor=gray93];\n" + this->walk() + "\n" + "}";
    }

private:
    std::string getDotName(){
        return "\"Nodo" + (this->id) + "\"";
    }

    std::string walk(){
        string cadena = "";

        cadena += (getDotName());
        cadena +=("[label=\"<P0>");
        for (int i = 0; i < num; i++){
            cadena +=("|" + std::to_string(this->keys[i]));
            cadena +=("|<P" + std::to_string((i + 1)) + ">");
        }
        cadena +=("\"];\n");
        for (int i = 0; i <= num; i++){
            if (children[i] != nullptr){
                cadena += (children[i]->walk());
                cadena += (getDotName() + ":P" + std::to_string(i) + " -> " + children[i]->getDotName() + ";\n");
            }
        }
        return cadena;
    }
};

string get_uuid(){
    static random_device dev;
    static mt19937 rng(dev());

    uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};
    string res;
    for(int i = 0; i < 16; i++){
        if(dash[i])
            res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}