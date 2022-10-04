//
// Created by Dmitrii Grigorev on 29.04.22.
//
#pragma once
#define RED "\e[0;31m"
#define BLUE "\e[0;36m"
#define LIGHT_GREY "\e[0;37m"
#define GREY "\e[0;90m"
#define WHITE "\e[0;38m"
#define WHITE_LINE "\e[4;37m"
#define RED_LINE "\e[4;31m"
#include "utils.hpp"
#include <iomanip>
#include <iostream>

namespace ftm {
    // Map node
    template <class T>
    struct node{
            typedef ftm::node<T> node_type;
            typedef node_type*   node_pointer;

            node_color color;
            T data;
            node_type * left;
            node_type * right;
            node_type * parent;

            node(T data)
                : data(data)
                , color(NODE_COLOR_BLACK)
                , left(NULL)
                , right(NULL)
                , parent(NULL) {};
            node_pointer getParent() { return parent; }
            node_pointer getGrandfather(){
                if(parent && parent->parent)
                    return parent->parent;
                return NULL;
            }
            node_pointer getSibling(){
                if(this->parent) {
                    if(data.first < parent->data.first) {
                        return parent->right;
                    } else {
                        return parent->left;
                    }
                }
                return NULL;
            }
            node_pointer getUncle(){
                if(!parent || !parent->parent)
                    return NULL;
                if(parent->data.first < parent->parent->data.first) {
                    return parent->parent->right;
                } else {
                    return parent->parent->left;
                }
            }
            bool isRight() {
                if(!parent)
                    return false;
                if(data.first < parent->data.first) {
                    return false;
                } else {
                    return true;
                }
            }
            bool isLeft() {
                if(!parent)
                    return false;
                if(data.first < parent->data.first) {
                    return true;
                } else {
                    return false;
                }
            }
            bool isRed() {
                return color == NODE_COLOR_RED;
            }
            bool isBlack() {
                return color == NODE_COLOR_BLACK;
            }
    };

    template<class Key, class T, class Compare = std::less<T>,
            class Allocator = std::allocator<T> >
    class map {
    public:
        typedef             Key 									                key_type;
        typedef             T 										                mapped_type;
        typedef             Allocator                               	            allocator_type;

        typedef             std::pair<const Key, T>					                value_type;

        typedef             node<value_type>                                        node_type;
        typedef             node_type*                                              node_pointer;

        typedef typename    Allocator::pointer        			                    pointer;
        typedef typename    Allocator::const_pointer  			                    const_pointer;
        typedef typename    Allocator::reference      			                    reference;
        typedef typename    Allocator::const_reference			                    const_reference;


        typedef             size_t                                                  size_type;
        typedef             ptrdiff_t                                               difference_type;

        typedef typename    allocator_type::template rebind<ftm::node<value_type> >::other	node_allocator_type;

        typedef             Compare									                key_compare;
        class               value_compare : std::binary_function<value_type, value_type, bool> {
            friend class map;
        public:
            bool operator()(const value_type &lhs, const value_type &rhs) const {
                return _comp(lhs.first, rhs.first);
            }
        protected:
            key_compare _comp;
            value_compare(key_compare comp) : _comp(comp) {}
        };

        map(): _root(NULL), _size(0) {
            createLeafNode();
        }
        map(const map& x) {
            createLeafNode();
        }
        ~map() {};

        allocator_type          get_allocator() const {return _allocator;}
        node_pointer            root(void) const {return _root;};

        // capacity
        bool                    empty() const {
            if(_root != NULL)
                return false;
            return true;
        };
        size_type               size() const{};
        size_type               max_size() const{};

//         modifiers
//        std::pair<iterator, bool>    insert(const value_type& x) {
//            insertStore(x);
//            std::pair<iterator,bool> res;
//            iterator it = begin();
//            res = std::make_pair(it,true);
//            return res;
//        };
        void    insert(const value_type& x) {
            insertStore(x);
        };

        node_pointer    find(const key_type& x) {
            node_pointer current = _root;
            while(current != NULL) {
                if(x == current->data.first)
                    return current;
                if(x < current->data.first) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return _leaf;
        };

    private:
        node_pointer    	_root;
        node_pointer        _leaf;
        size_type			_size;
        node_allocator_type _node_allocator;
        allocator_type      _allocator;
        key_compare         _cmp;

        void   log(std::string place ,node_pointer p){
            std::cout << place << " : " << p << "\n";
        }
        void   log(std::string place ,size_t msg){
            std::cout << place << " : " << std::to_string(msg) << "\n";
        }
        void   log(std::string place ,std::string msg){
            std::cout << place << " : " << msg << "\n";
        }
        void   log(std::string place){
            std::cout << place << "\n";
        }
        void            createLeafNode() {
            _leaf  = _node_allocator.allocate(1);
            _node_allocator.construct(_leaf, value_type());
            _leaf->color = NODE_COLOR_BLACK;
            _leaf->parent = NULL;
            _leaf->left = NULL;
            _leaf->right = NULL;
        }
        node_pointer    createNode(const value_type& x, node_pointer parent) {
            node_pointer node  = _node_allocator.allocate(1);
            _node_allocator.construct(node, x);
            node->color = NODE_COLOR_RED;
            node->left = _leaf;
            node->right = _leaf;
            node->parent = parent;
            return node;
        }
        node_pointer    insertEntry(const value_type& x) {
            node_pointer current = _root;
            node_pointer previous = _root->parent;
            while(current != _leaf) {
                previous = current;
                if(x.first < current->data.first) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            if(previous->data.first > x.first){
                previous->left = createNode(x, previous);
                return previous->left;
            } else {
                previous->right = createNode(x, previous);
                return previous->right;
            }
        }

        node_pointer rotateLeft(const node_pointer root) {
            log("rotate L", root->data.first);
            node_pointer newRoot, newLeft, b;
            newRoot = root->right;
            newLeft = root;
            b = newRoot->left;
            if (!root->parent) {
                _root = newRoot;
            } else if (root->isLeft()) {
                root->parent->left = newRoot;
            } else if (root->isRight()) {
                root->parent->right = newRoot;
            }
            newRoot->parent = root->parent;
            newRoot->left = newLeft;
            newLeft->parent = newRoot;
            b->parent = newLeft;
            newLeft->right = b;
//            log("_root", _root->data.first);
//            log("newRoot P", newRoot->parent);
//            log("newRoot", newRoot->data.first);
//            log("newRoot L", newRoot->left->data.first);
//            log("newRoot R", newRoot->right->data.first);
//            log("newRoot L P", newRoot->left->parent->data.first);
//            log("newRoot R P", newRoot->right->parent->data.first);
            return newRoot;
        }
        node_pointer rotateRight(const node_pointer root){
            log("rotate R", root->data.first);
            node_pointer newRoot, newRight,b;
            newRoot = root->left;
            newRight = root;
            b = newRoot->right;
            if(!root->parent){
                _root = newRoot;
            }
            else if(root->isLeft()){
                root->parent->left = newRoot;
            }
            else if(root->isRight()){
                root->parent->right = newRoot;
            }
            newRoot->parent = root->parent;
            newRoot->right = newRight;
            newRight->parent = newRoot;
            b->parent = newRight;
            newRight->left = b;
//            log("_root", _root->data.first);
//            log("newRoot P", newRoot->parent);
//            log("newRoot", newRoot->data.first);
//            log("newRoot L", newRoot->left->data.first);
//            log("newRoot R", newRoot->right->data.first);
//            log("newRoot L P", newRoot->left->parent->data.first);
//            log("newRoot R P", newRoot->right->parent->data.first);
            return newRoot;
        }

        node_pointer     balanceInsert(int insertCase,node_pointer node) {
            switch (insertCase) {
                case 0:
                case 1: {
                    return NULL;
                }
                case 2: {
                    log("insert", "case 2");
                    node->getParent()->color       = NODE_COLOR_BLACK;
                    node->getGrandfather()->color  = NODE_COLOR_RED;
                    node->getUncle()->color        = NODE_COLOR_BLACK;
                    node = node->parent;
                    break;
                }
                case 3: {
                    return NULL;
                }
                case 4: {
                    node->getParent()->color = NODE_COLOR_BLACK;
                    break;
                }
                case 51: {
                    log("insert", "case 51");
                    rotateLeft(node->parent);
                    node = node->left;
                }
                case 60: {
                    log("insert", "case 60");
                    node = rotateRight(node->parent->parent);
                    node->color = NODE_COLOR_BLACK;
                    node->right->color = NODE_COLOR_RED;
                    break;
                }
                case 50: {
                    log("insert", "case 50");
                    rotateRight(node->parent);
                    node = node->right;
                }
                case 61: {
                    log("insert", "case 61");
                    node = rotateLeft(node->parent->parent);
                    node->color = NODE_COLOR_BLACK;
                    node->left->color = NODE_COLOR_RED;
                    break;
                }
            }

            return node->parent;
        }

        void            insertStore(const value_type& x) {
            log("\nnow inserting", x.first);
            if(find(x.first) != _leaf) {
                return;
            }
            if(this->empty()) {
                _root = createNode(x, _root);
                _root->color = NODE_COLOR_BLACK;
                return;
            }
            node_pointer place = insertEntry(x);

            int         insertCase = 0;
            while(place != NULL) {
                log("now balancing", place->data.first);
                if(place->getGrandfather())
                    std::cout << place->getGrandfather() << "|" << place->getParent()->isRed() << "|" << place->getUncle()->isRed() << "|" << place->getGrandfather()->isBlack()<< "\n";
                if(place->getParent() && place->getParent()->isBlack()) {           //  Insert case 1   Parent is BLACK
                        insertCase = 1;
                }
                else if(place->getGrandfather() && place->getParent()->isRed() \
                                          && place->getUncle()->isRed() \
                                          && place->getGrandfather()->isBlack()) {  //  Insert case 2   Parent && Uncle is RED && Grand is BLACK
                        insertCase = 2;
                }
                else if((!place->parent && place->color == NODE_COLOR_RED)) {
                        place->color = NODE_COLOR_BLACK;
                        insertCase = 3;
                }
                else if(place->getParent() && place->getParent()->isRed() && !place->getGrandfather()) { //  Insert case 4   Parent is RED && no Grand
                        insertCase = 4;
                }
                else if(place->getUncle() && place->getParent()->isRed() \
                                          && !place->getUncle()->isRed() \
                                          && place->getGrandfather()->isBlack()) { //  Insert case 5   Parent is RED && Uncle BLACK && Grand BLACK &&
                    if(place->isLeft()) {
                        if(place->parent->isLeft())
                            insertCase = 60;
                        else
                            insertCase = 50;
                    }
                    else {
                        if(place->parent->isRight())
                            insertCase = 61;
                        else
                            insertCase = 51;
                    }
                }
                else { // Bad place

                }
                place = balanceInsert(insertCase,place);
            }

        }
    };
}