//
// Created by Dmitrii Grigorev on 29.04.22.
////
#include <iomanip>
#include <unistd.h>
#define RED "\e[0;31m"
#define BLUE "\e[0;36m"
#define LIGHT_GREY "\e[0;37m"
#define GREY "\e[0;90m"
#define WHITE "\e[0;38m"
#define WHITE_LINE "\e[4;37m"
#define RED_LINE "\e[4;31m"
#include <iostream>
#include <list>
using namespace std;

namespace ft{
    typedef struct      s_node node;
    struct s_node{
            node*   parent;
            node*   left;
            node*   right;
            int     key;
            int     val;
            bool    color; //  0 black / 1 red

    };
    class map{
        public:
            map(): _root(nullptr), _debug(0){};
            map(int key, int val) : _debug(0) {
    //                cout << "create root node " << key <<"\n";
                createRootNode(key,val);
            }
            ~map(){};
            void    append(int key,int val){
                if(_debug)
                    std::cout << RED << ">>> append "<<key << WHITE<<"\n";
                if(!_root) {
                    createRootNode(key, val);
                    return;
                }
                node* ptr = _root;
                node* nodeNew = createNode(key,val);
                while(1) {
                    if (nodeNew->key > ptr->key)
                    {
                        if(ptr->right && ptr->right->key)
                            ptr=ptr->right;
                        else
                        {
                            nodeNew->parent = ptr;
                            ptr->right = nodeNew;
                            cout << "\nadd " << key << "\n";
                            balanceAdd(ptr->right);
                            break;
                        }
                    }
                    else if (nodeNew->key < ptr->key)
                    {
                        if(ptr->left && ptr->left->key)
                            ptr=ptr->left;
                        else
                        {
                            nodeNew->parent = ptr;
                            ptr->left = nodeNew;
                            cout << "\nadd " << key << "\n";
                            balanceAdd(ptr->left);
                            break;
                        }
                    }
                    else
                        return;
                }
            };
            void    print(int level, node *ptr)
            {
                int i;
                if (ptr != NULL)
                {
                    print(level + 1, ptr->right);
                    cout << "\n";
                    for (i = 0; i < level && ptr != _root; i++)
                        cout << "     ";
                    if(ptr->color)
                        printNodeAdr(ptr,1);
                    else
                        printNodeAdr(ptr,0);
                    print(level + 1, ptr->left);
                }
            }
            void    printNodeAdr(node* ptr, bool color){
                if(_debug)
                {
                    cout << BLUE;
                    if (ptr->parent)
                        cout << to_string((long) ptr->parent).substr(13, 2);
                    else
                        cout << "00";
                }
                cout << GREY;

                if(color)
                    cout << RED_LINE << ptr->key << GREY;
                else
                    cout << WHITE_LINE << ptr->key << GREY;
                if(_debug) {
                    cout << BLUE << to_string((long) ptr).substr(13, 2) << GREY;

                    if (ptr->left)
                        cout << to_string((long) ptr->left).substr(13, 2);
                    else
                        cout << "00";

                    if (ptr->right)
                        cout << to_string((long) ptr->right).substr(13, 2);
                    else
                        cout << "00";
                }
                cout << WHITE;
            }
            void    setDebugMode() {_debug = 1;};
            node*   getRoot(){return _root;}
            void    erase(int key)
        {
            if(_debug) {
                cout << RED << "\n>>> erase " << key << WHITE << "\n";
                std::cout << "\n";
            }
            node* ptr = findByKey(key);
            if (!ptr)
                return;
            // deleting not leaf node
            if (ptr->left->key && ptr->right->key) {
                cout << "erase: left leaf & right leaf: replace successor \n";
                balanceDelete(replaceSuccessor(ptr));
            } else {
//                 deleting inside 3-node
                if (!ptr->right->key && ptr->left->key && ptr->left->color) {
                    cout << "erase:"<<RED<<" left"<<WHITE<<" & !right \n";
                    deleteLeafNode(ptr->right);
                    ptr->right = nullptr;
                    ptr->right = ptr->left->right;
                    ptr->key = ptr->left->key;
                    ptr->val = ptr->left->val;
                    deleteLeafNode(ptr->left);
                    ptr->left = createNullNode(ptr->left);
                    balanceDelete(ptr);
                    // deleting leaf node
                } else if (!ptr->right->key && !ptr->left->key) {
                    cout << "erase: no left leaf & no right leaf \n";
                    deleteLeafNode(ptr->left);
                    deleteLeafNode(ptr->right);
                    ptr->left = nullptr;
                    ptr->right = nullptr;
                    ptr->key = 0;
                    ptr->val = 0;
                    ptr->color = 0;
                    balanceDelete(ptr);
                }
            }
//            print(1,_root);
        }
        private:
            node*   _root;
            bool _debug;

            void    createRootNode(int key, int val){
                if(_debug)
                    std::cout << "createRootNode "<<key<<"\n";
            _root = new node();
            _root->key = key;
            _root->val = val;
            _root->parent = nullptr;
            _root->left = createNullNode(_root->left);
                _root->left->parent = _root;
            _root->right = createNullNode(_root->right);
                _root->right->parent = _root;
            _root->color = 0;
            };
            node*   createNode(int key = 0, int val = 0){
            node* newNode = new node;
            newNode->key = key;
            newNode->val = val;
            newNode->color = 1;
            newNode->parent = nullptr;
            newNode->left = createNullNode(newNode->left);
            newNode->left->parent = newNode;
            newNode->right = createNullNode(newNode->right);
            newNode->right->parent = newNode;
            return newNode;
            };
            node*   createNullNode(node* ptr){
                if(_debug)
                    std::cout << "createNullNode "<<"\n";
                node* nullNode = new node;
                nullNode->key = 0;
                nullNode->val = 0;
                nullNode->color = 0;
//                nullNode->parent = nullptr;
                nullNode->parent = ptr;
                nullNode->left = nullptr;
                nullNode->right = nullptr;
                return nullNode;
            };
            void    balanceAdd(node* ptr){
                if(_debug)
                    std::cout << "balance "<<"\n";
                while(ptr)
                {
                    if (!ptr->left->color && ptr->right->color)
                        turnLeft(ptr);
                    if (ptr->left->color && ptr->right->color)
                        colorSwap(ptr);
                    if (ptr->left->left && ptr->left->left->color && ptr->left->color)
                        turnRight(ptr);
                    ptr = ptr->parent;
                }
            }
            void    turnLeft(node* ptr){
//                print(1,_root);
                if(_debug)
                    cout << "\nturnLeft " << ptr->key << "\n";
                node* newLeft = ptr;
                node* newRoot;
                if(ptr->parent) {
                    if (ptr->parent->right->key == ptr->key) {
                        ptr->parent->right = ptr->right;
                    } else if (ptr->parent->left->key == ptr->key) {
                        ptr->parent->left = ptr->right;
                    }
                    newRoot = ptr->right;
                    newRoot->parent = ptr->parent;
                } else {
                    _root = ptr->right;
                    newRoot = _root;
                    newRoot->parent = nullptr;
                }
                newLeft->parent = nullptr;
                newLeft->right = ptr->right->left;

                int rootColor = newRoot->color;
                newRoot->color = newLeft->color;
                newLeft->color = rootColor;

                newRoot->left = newLeft;
                newLeft->parent = newRoot;
                newLeft->right->parent = newLeft;
            }
            void    turnRight(node* ptr) {
                if(_debug)
                    cout << "\nturnRight " << ptr->key << "\n";
                node* newRight = ptr;
                node* newRoot;
                if(ptr->parent) {
                    if (ptr->parent->right->key == ptr->key) {
                        ptr->parent->right = ptr->left;
                    }
                    else if (ptr->parent->left->key == ptr->key) {
                        ptr->parent->left = ptr->left;
                    }
                    newRoot = ptr->left;
                    newRoot->parent = ptr->parent;
                }
                else {
                    _root = ptr->left;
                    newRoot = _root;
                    newRoot->parent = nullptr;
                }
                newRight->parent = nullptr;
                newRight->left = ptr->left->right;
                newRoot->color = 0;
                newRoot->right = newRight;
                newRight->parent = newRoot;
                newRight->color = 1;
                newRight->left->parent = newRight;
                colorSwap(newRoot);
            }
            void    colorSwap(node* ptr){
                if(_debug)
                    cout << "\ncolorSwap " << ptr->key << "\n";
                ptr->left->color=0;
                ptr->right->color=0;
                if(ptr->parent)
                    ptr->color = 1;
            }
            node*   findByKey(int key)
            {
                node* res = _root;
                while(res)
                {
                    if(res->key == key)
                        break;
                    if(res->key > key)
                        res = res->left;
                    else
                        res = res->right;
                }
                return res;
            }
            void    deleteLeafNode(node* ptr){
            ptr->parent = NULL;
            ptr->left = NULL;
            ptr->right = NULL;
            ptr->color=0;
            delete ptr;
            ptr = NULL;
        }
            node*   replaceSuccessor(node* ptr) {
                node* succ = ptr;
                cout << "replace successor: " << succ->key << " to ";
                succ = succ->right;
                while(succ && succ->left && succ->left->key)
                    succ = succ->left;
                cout << succ->key << "\n";
                cout << "deleted node with former key " << succ->key << "\n";
                ptr->key = succ->key;
                ptr->val = succ->val;
                deleteLeafNode(succ->left);
                deleteLeafNode(succ->right);
                succ->left = nullptr;
                succ->right = nullptr;
                succ->val = 0;
                succ->key = 0;
                succ->color = 0;
                return succ;
            }
            void    balanceDelete(node* deleted)
            {
                if(_debug)
                    cout << "\nbalance delete "  << "\n";
                node* parent = deleted->parent;
                if (!parent) {
                    cout << "\n!this is root -> done "  << "\n";
                    return;
                }
                cout << "balance delete: balance at " << parent->key << " ";
                if (!parent->left->key && !parent->right->key) {
                    cout << "no leaf nodes -> done "  << "\n";
                    return;
                }
                if (parent->left->key && parent->left->color) {
                    // case 1.1: left Red   - share
                    cout << "left is RED -> share " << parent->key << "\n";
                    turnRight(parent);
                    parent->left->color = 1;
                    if(parent->parent)
                    {
                        parent->parent->color = 0;
                        parent->parent->left->color = 0;
                    }
                    return;
                }
                if (parent->left->key || parent->right->key) {
                    cout << "- right is deleted- left is black -> merge\n";
                    join(parent);
                    balanceDelete(parent);
    //                     case 1.2: left Black - merge
                    return;
                }
            }
            void    join(node* emptyNode){
                node* a,b,c,d,newEmpty,grandParent,new3black,new3red;
                short type = 2;
                // my sibling left or right?
                if(emptyNode->parent->left && emptyNode->parent->left == emptyNode) {
                    type = 0;
                    std::cout << "join: im in left";
                }
                if(emptyNode->parent->left && emptyNode->parent->right == emptyNode) {
                    type = 1;
                    std::cout << "join: im in right";
                }
                switch (type) {
                    // empty is right
                    case 1: {
                        printf("\nempty:%llu|gp:%llu|a:%llu|b:%llu|c:%llu|d:%llu|\n",emptyNode,emptyNode->parent,emptyNode->parent->left->left,emptyNode->parent->left->right,emptyNode->left,emptyNode->right);
                        break;
                    }
                    // empty is left
                    case 0: {
                        break;
                    }
                    default: return;
                }
            };
    };
}


int main(int argc, char** argv)
{
    ft::map map;
    if(argc>1) {
        cout << "<<< DEBUG MODE >>>\n";
        map.setDebugMode();
    }
    map.append(1,99);
    map.append(2,99);
    map.append(3,99);
    map.append(4,99);
    map.append(5,99);
    map.append(6,99);
    map.append(7,99);
    map.append(8,99);
//    map.append(9,99);
//    map.append(10,99);
//    map.append(11,99);
//    map.append(12,99);
//    map.append(13,99);
//    map.append(14,99);
//    map.append(15,99);
//    map.append(16,99);
//    map.append(24,99);
//    map.print(1,map.getRoot());
//    map.append(50,99);
//    map.print(1,map.getRoot());
//    map.append(11,99);
//    map.print(1,map.getRoot());
//    map.append(10,99);
//    map.append(9,99);
//    map.append(8,99);
//    map.erase(13);
//    map.erase(6);
//    map.print(1,map.getRoot());
    map.erase(7);
    map.print(1,map.getRoot());
    map.erase(8);
    return 0;
}

//