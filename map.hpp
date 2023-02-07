//
// Created by Dmitrii Grigorev on 29.04.22.
//
#pragma once
#include "utils.hpp"
#include <iomanip>
#include <iostream>
#include "./map_iterator.hpp"
#include "./reverse_iterator.hpp"

namespace ft {
    // Map node
    template <class T>
    struct node{
            typedef ft::node<T>     node_type;
            typedef T               value_type;
            typedef node_type*      node_pointer;

            node_color  color;
            value_type* data;
            node_type*  left;
            node_type*  right;
            node_type*  parent;

            node(value_type value)
                : data(value)
                , color(NODE_COLOR_BLACK)
                , left(NULL)
                , right(NULL)
                , parent(NULL) {};
            node_pointer getParent() { return parent; }
//            value_type getValue(){
//                return data;
//            }
            node_pointer getSibling(){
            if(this->parent) {
                if(parent->left == this) {
//                    std::cout << "getSibling " << this << " : p " << parent->data.first << " : l " << parent->left->data.first << " : r " << parent->right->data.first << " : s " << parent->right->data.first << "\n";
                    return parent->right;
                } else {
//                    std::cout << "getSibling " << this << " p " << parent->data.first << " : l " << parent->left->data.first << " : r " << parent->right->data.first << " : s " << parent->left->data.first << "\n";
                    return parent->left;
                }
            }
            return NULL;
        }
            node_pointer getCloseNepfew() {
                if(!getSibling()) {
                    return NULL;
                }
                return isLeft() ? getSibling()->left : getSibling()->right;
            }
            node_pointer getDistantNepfew() {
                if(!getSibling()) {
                    return NULL;
                }
                return isLeft() ? getSibling()->right : getSibling()->left;
            }
            node_pointer getGrandfather(){
                if(parent && parent->parent)
                    return parent->parent;
                return NULL;
            }
            node_pointer getUncle(){
                if(!parent || !parent->parent)
                    return NULL;
                if(parent->data->first < parent->parent->data->first) {
                    return parent->parent->right;
                } else {
                    return parent->parent->left;
                }
            }
            bool isRight() {
                if(!parent)
                    return false;
                if(parent->left == this) {
                    return false;
                } else {
                    return true;
                }
            }
            bool isLeft() {
                if(!parent)
                    return false;
                if(parent->left == this) {
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
            T* operator*(){
                return this->data;
            }
            T* operator->(){
            return *(this->data);
        }
    };

    template<class Key, class T, class Compare = std::less<Key>,
            class Allocator = std::allocator<ft::pair<const Key,T> > >
    class map {
    public:
        typedef             Key 									                key_type;
        typedef             T 										                mapped_type;
        typedef             Allocator                               	            allocator_type;
        typedef             ft::pair<const Key, T>					                value_type;
        typedef             node<value_type>                                        node_type;
        typedef             node_type*                                              node_pointer;
        typedef typename    Allocator::pointer        			                    pointer;
        typedef typename    Allocator::const_pointer  			                    const_pointer;
        typedef typename    Allocator::reference      			                    reference;
        typedef typename    Allocator::const_reference			                    const_reference;
        typedef             size_t                                                  size_type;
        typedef             ptrdiff_t                                               difference_type;
        typedef             Compare									                key_compare;
        typedef             MapIterator<node_type>					                iterator;
        typedef             const_MapIterator<node_type>				            const_iterator;
        typedef             ft::reverse_iterator<iterator>							reverse_iterator;
        typedef             ft::reverse_iterator<const_iterator>					const_reverse_iterator;
        typedef typename    allocator_type::template rebind<ft::node<value_type> >::other	node_allocator_type;

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
            *this = x;
        }
        ~map() {};

        template <class InputIterator>
        map (
                InputIterator first,
                InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()
        ) : _root(NULL), _size(0) {
            createLeafNode();
            while(first != last)
            {
                insert(*first);
                first++;
            }
        }

        allocator_type          get_allocator() const {return _allocator;}
        node_pointer            root(void) const {return _root;};
        // capacity
        bool                    empty() const {
            if(_root != NULL)
                return false;
            return true;
        };

        size_type               size() const{
            return _size;
        };
        size_type               max_size() const{};

        void    insert(const value_type& x) {
            insertStore(x);
        }
        void    erase(const key_type& k) {
            eraseStore(k);
        }
        iterator    find(const key_type& x) {
            node_pointer current = _root;
            while(current && current->data) {
                if(x == current->data->first)
                    return iterator(current, this->begin().getPtr(), _leaf);
                if(x < current->data->first) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return end();
        };

        const_iterator   find(const key_type& x) const {
            node_pointer current = _root;
            while(current && current->data) {
                if(x == current->data->first)
                    return const_iterator(current, this->begin().getPtr(), _leaf);
                if(x < current->data->first) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return end();
        };
        iterator lower_bound (const key_type& key)
        {
            iterator it = this->begin();
            iterator end = this->end();
            while(it != end && key_comp()(it->first, key))
                it++;
            return (it);
        }

        const_iterator lower_bound (const key_type& key) const
        {
            const_iterator it = begin();
            const_iterator end = end();
            while(it != end && key_comp()(it->first, key))
                it++;
            return (it);
        }

        iterator upper_bound (const key_type& key)
        {
            iterator it = begin();
            iterator end = end();
            while(it != end && !key_comp()(key, it->first))
                it++;
            return (it);
        }

        const_iterator upper_bound (const key_type& key) const
        {
            const_iterator it = begin();
            const_iterator end = end();
            while(it != end && !key_comp()(key, it->first))
                it++;
            return (it);
        }
        key_compare key_comp() const
        {
            return (_cmp);
        }
        value_compare value_comp() const
        {
            return value_compare(_cmp);
        }
        pair<iterator,iterator> equal_range (const key_type& key)
        {
            return (ft::make_pair(lower_bound(key), upper_bound(key)));
        }

        pair<const_iterator,const_iterator> equal_range (const key_type& key) const
        {
            return (ft::make_pair(lower_bound(key), upper_bound(key)));
        }
        size_type       count( const Key& key ) const
        {
            if (findPointer(key) == _leaf)
                return (0);
            return (1);
        }
        iterator        begin(){
            node_pointer node = this->_root;
            while(node->left != _leaf){
                node = node->left;
            }
            return iterator(node,node,_leaf);
        }
        const_iterator  begin() const{
            node_pointer node = this->_root;
            while(node->left != _leaf){
                node = node->left;
            }
            return const_iterator(node,node,_leaf);
        }
        iterator        end(){
            node_pointer node = this->_root;
            while(node->left != _leaf){
                node = node->left;
            }
            return iterator(_leaf,node,_leaf);
        }
        const_iterator  end() const {
            return const_iterator(_leaf, this->begin().getPtr(),_leaf);
        }
        mapped_type     at(const Key &key)
        {
            node_pointer n = this->findPointer(key);
            if (n != _leaf)
                return(n->data->second);
            throw std::out_of_range("key not found");
        }
        mapped_type&    operator[](const Key &key)
        {
            node_pointer n = this->findPointer(key);
            if (n == _leaf)
                insert(ft::make_pair(key, T()));
            n = this->findPointer(key);
            return (n->data->second);
        }

    private:
        node_pointer    	_root;
        node_pointer        _leaf;
        size_type			_size;
        node_allocator_type _node_allocator;
        allocator_type      _allocator;
        key_compare         _cmp;

        node_pointer    findPointer(const key_type& x) {
            node_pointer current = _root;
            while(current != NULL && current->data && current->data->first) {
                if(x == current->data->first)
                    return current;
                if(x < current->data->first) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return _leaf;
        };
        node_pointer    findPointer(const key_type& x) const {
            node_pointer current = _root;
            while(current != NULL && current->data && current->data->first) {
                if(x == current->data->first)
                    return current;
                if(x < current->data->first) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return _leaf;
        };
        void            swap_4_replacing_in_children(node_pointer a, node_pointer b, node_pointer ap, node_pointer bp) {
            a->left->parent = a;
            a->right->parent = a;
            b->left->parent = b;
            b->right->parent = b;
        }
        void            swap_3_replacing_children(node_pointer a, node_pointer b, node_pointer ap, node_pointer bp){
            node_pointer al,ar,bl,br;
            al = a->left;
            ar = a->right;
            bl = b->left;
            br = b->right;
            if(ap == b) {
                if(b->left == a) {
                    b->left = al;
                    b->right = ar;
                    a->left = b;
                    a->right = br;
                } else {
                    a->left = bl;
                    a->right = b;
                    b->left = al;
                    b->right = ar;
                }
                return;
            }
            if(bp == a) {
                if(a->left == b) {
                    a->left = bl;
                    a->right = br;
                    b->left = a;
                    b->right = ar;
                } else {
                    a->left = bl;
                    a->right = br;
                    b->right = a;
                    b->left = al;
                }
                return;
            }
            ft::swap(a->left, b->left);
            ft::swap(a->right, b->right);
        }
        void            swap_2_replacing_parents(node_pointer a, node_pointer b, node_pointer ap, node_pointer bp) {
            if(!ap) {
                _root = b;
                a->parent = bp;
                b->parent = NULL;
                return;
            }
            if(!bp) {
                _root = a;
                b->parent = ap;
                a->parent = NULL;
                return;
            }
            if(ap == b){
                b->parent = a;
                a->parent = bp;
                return;
            }
            if(bp == a){
                a->parent = b;
                b->parent = ap;
                return;
            }
            ft::swap(a->parent,b->parent);
        }
        void            swap_1_replacing_in_parents(node_pointer a, node_pointer b) {
            if(a->parent && a->parent == b) {
                if(b->parent) {
                    if(b->isLeft()) {
                        b->parent->left = a;

                    } else {
                        b->parent->right = a;
                    }
                } else {
                    _root = a;
                }
                return;
            }
            if(b->parent && b->parent == a) {
                if(a->parent) {
                    if(a->isLeft()) {
                        a->parent->left = b;

                    } else {
                        a->parent->right = b;
                    }
                } else {
                    _root = b;
                }
                return;
            }
            if(b->parent) {
                if(b->isLeft()) {
                    b->parent->left = a;

                } else {
                    b->parent->right = a;
                }
            } else {
                _root = a;
            }
            if(a->parent) {
                if(a->isLeft()) {
                    a->parent->left = b;

                } else {
                    a->parent->right = b;
                }
            } else {
                _root = b;
            }
        }
        void            swap(node_pointer a, node_pointer b){
//            std::cout <<"swap: "<< a->data.first << " " << b->data.first << "\n";
            node_pointer ap,bp;
            ap = a->parent;
            bp = b->parent;
            swap_1_replacing_in_parents(a,b);

            swap_2_replacing_parents(a,b,ap,bp);
            swap_3_replacing_children(a,b,ap,bp);
            swap_4_replacing_in_children(a,b,ap,bp);
            ft::swap(a->color,b->color);
        }
        void            deleteMeFromParent(node_pointer me){
            if(!me->parent)
                return;
            if(me == me->parent->left) {
                me->parent->left = _leaf;
            } else {
                me->parent->right = _leaf;
            }
        }
        void            replaceMeFromParent(node_pointer me, node_pointer replacement){
            if(!me->parent) {
                _root = replacement;
                return;
            }
            if(me == me->parent->left) {
                me->parent->left = replacement;
            } else {
                me->parent->right = replacement;
            }
        }
        void            createLeafNode() {
            _leaf = _node_allocator.allocate(1);
            _leaf->color = NODE_COLOR_BLACK;
            _leaf->parent = NULL;
            _leaf->left = NULL;
            _leaf->right = NULL;
            _leaf->data = NULL;
        }
        node_pointer    createNode(const value_type& x, node_pointer parent) {
            node_pointer node  = _node_allocator.allocate(1);
            node->color = NODE_COLOR_RED;
            node->left = _leaf;
            node->right = _leaf;
            node->parent = parent;

            node->data = _allocator.allocate(1);
            _allocator.construct(node->data,x);
            return node;
        }
        node_pointer    insertEntry(const value_type& x) {
            node_pointer current = _root;
            node_pointer previous = _root->parent;
            while(current != _leaf) {
                previous = current;
                if(x.first < current->data->first) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            if(previous->data->first > x.first){
                previous->left = createNode(x, previous);
                return previous->left;
            } else {
                previous->right = createNode(x, previous);
                return previous->right;
            }
        }
        node_pointer    rotateLeft(const node_pointer root) {
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
            if(b!= _leaf)
                b->parent = newLeft;
            newLeft->right = b;
            return newRoot;
        }
        node_pointer    rotateRight(const node_pointer root){
            node_pointer newRoot, newRight,b;
            newRoot = root->left;
            newRight = root;
            b = newRoot->right;
//            std::cout << "rotate R newRoot " << newRoot->data.first << " newRight " <<  newRight->data.first << " b " <<  b->data.first << "\n";
            if(!root->parent){
                _root = newRoot;
            } else if(root->isLeft()){
                root->parent->left = newRoot;
            } else if(root->isRight()){
                root->parent->right = newRoot;
            }
//            std::cout << newRoot->parent->data.first << " " << newRoot->parent->right->data.first << "\n";
            newRoot->parent = root->parent;
            newRoot->right = newRight;
            newRight->parent = newRoot;
            if(b!= _leaf)
                b->parent = newRight;
            newRight->left = b;
            return newRoot;
        }
        node_pointer    balanceInsert(int insertCase,node_pointer node) {
            switch (insertCase) {
                case 0:
                    return NULL;
                case 1: {
                    return NULL;
                }
                case 2: {
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
                    rotateLeft(node->parent);
                    node = node->left;
                }
                case 60: {
                    node = rotateRight(node->parent->parent);
                    node->color = NODE_COLOR_BLACK;
                    node->right->color = NODE_COLOR_RED;
                    break;
                }
                case 50: {
                    rotateRight(node->parent);
                    node = node->right;
                }
                case 61: {
                    node = rotateLeft(node->parent->parent);
                    node->color = NODE_COLOR_BLACK;
                    node->left->color = NODE_COLOR_RED;
                    break;
                }
            }
            return node->parent;
        }
        void            deleteNode(node_pointer node) {
            _node_allocator.destroy(node);
            _node_allocator.deallocate(node,1);
        }
        void            insertStore(const value_type& x) {
            if(findPointer(x.first) != _leaf) {
                return;
            }
            if(this->empty()) {
                _root = createNode(x, _root);
                _root->color = NODE_COLOR_BLACK;
                _size++;
                return;
            }
            _size++;
            node_pointer place = insertEntry(x);
            int         insertCase = 0;
            while(place != NULL) {
                if(place->getParent() \
                && place->getParent()->isBlack()) {                               //  Insert case 1   Parent is BLACK
                        insertCase = 1;
                }
                else if(place->getGrandfather()
                     && place->getParent()->isRed() \
                     && place->getUncle()->isRed() \
                     && place->getGrandfather()->isBlack()) {                      //  Insert case 2   Parent && Uncle is RED && Grand is BLACK
                        insertCase = 2;
                }
                else if((!place->parent && place->color == NODE_COLOR_RED)) {
                        place->color = NODE_COLOR_BLACK;
                        insertCase = 3;
                }
                else if(!place->parent) {
                        insertCase = 1;
                }
                else if(place->getParent() && place->getParent()->isRed() && !place->getGrandfather()) { //  Insert case 4   Parent is RED && no Grand
                        insertCase = 4;
                }
                else if(place->getUncle() && place->getParent()->isRed() \
                                          && place->getUncle()->isBlack() \
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
                place = balanceInsert(insertCase,place);
                if(insertCase == 60 || insertCase == 61 || insertCase == 50 || insertCase == 51)
                    return;
            }
        }
        node_pointer    getSuccessor(node_pointer node) {
            node_pointer succ;


            if (node->right && node->right != _leaf) {
                succ = node->right;
                while (succ->left && succ->left != _leaf) {
                    succ = succ->left;
                }
            }
            else if(node->left && node->left != _leaf) {
                succ = node->left;
                while(succ->right && succ->right != _leaf) {
                    succ = succ->right;
                }
            }
            else
                return node;
            return succ;
        }
        bool            replaceBySuccessor(node_pointer node){

            bool blackDeleted = 0;
            node_pointer successor = getSuccessor(node);
            swap(node, successor);
            if(node->right != _leaf) {
                _leaf->parent = node->right;
                node->right->color = NODE_COLOR_BLACK;
                node->right->parent = node->parent;
                replaceMeFromParent(node,node->right);
                deleteNode(node);
            } else if(node->right == _leaf) {
                if(node->isBlack()) {
                    blackDeleted = 1;
                }
                deleteMeFromParent(node);
                deleteNode(node);
            }
            return blackDeleted;
        }
        void            eraseStore(const key_type& k) {
            if(findPointer(k) == _leaf) {
                return;
            }
            node_pointer node = findPointer(k);
            // erase root no child
            if(!node->parent && node->left == _leaf && node->right == _leaf) {
                deleteNode(node);
                deleteMeFromParent(node);
                _root = NULL;
                return;
            }
            // erase non-root red
            else if(node->color == NODE_COLOR_RED && (node->left == _leaf && node->right == _leaf)) {
                deleteNode(node);
                deleteMeFromParent(node);
                return;
            }
            // erase root one red child
            else if((node->left == _leaf && node->right != _leaf) || (node->left != _leaf && node->right == _leaf)) {
                if (node->left != _leaf) {
                    std::cout << node << " " << node->left << "\n";
                    swap(node, node->left);
                    replaceMeFromParent(node, node->left);
                } else {
//                    std::cout << node << " " << node->right << "\n";
                    swap(node, node->right);
                    replaceMeFromParent(node, node->right);
                }
                deleteNode(node);
                // erase black no child
            } else if(node->color == NODE_COLOR_BLACK && (node->left == _leaf && node->right == _leaf)) {
                    _leaf->parent = node->parent;
                    node_pointer startBalance = _leaf;
//                    std::cout << "startBalance: " << startBalance->data.first << "\n";
                    deleteMeFromParent(node);
                    deleteNode(node);
                    balanceDelete(startBalance);
                // erase two children
            } else if(node->left != _leaf && node->right != _leaf) {
                    node_pointer balanceStart;
                    balanceStart = _leaf;
                    bool deletedBlack = replaceBySuccessor(node);
                    _leaf->parent = node->parent;
                    if(deletedBlack) {
                        balanceDelete(balanceStart);
                    }
            } else {
            }
        }
        void            balanceDelete(node_pointer node) {
            while(node != NULL) {
                int deleteCase = 0;
                if (node->data.first) {
                }
                if(node->getSibling() && node->getSibling()->color) {
                    deleteCase = 3;
                } else if (node->getDistantNepfew() && node->getDistantNepfew()->color) {
                    deleteCase = 6;
                } else if(node->getCloseNepfew() && node->getCloseNepfew()->color) {
                    deleteCase = 5;
                } else if(node->parent && node->parent->color) {
                    deleteCase = 4;
                } else if (node->parent && !node->parent->color && node->getSibling() && !node->getSibling()->color &&
                    node->getCloseNepfew() && node->getDistantNepfew() && !node->getCloseNepfew()->color &&
                    !node->getDistantNepfew()->color) {
                    deleteCase = 1;
                // erase black non-root case 2 // is root
                } else if (!node->parent) {
                    deleteCase = 2;
                    // erase black non-root case 6 // 1-2-3-4-5-6-7-8-9-666 erase 1
                }
                node = deleteBalanceLevel(node, deleteCase);
            }
        }
        node_pointer           deleteCase1(node_pointer node) {
            node->getSibling()->color = NODE_COLOR_RED;
            return node->parent;
        }
        node_pointer           deleteCase4(node_pointer node){
            node->getSibling()->color = NODE_COLOR_RED;
            node->getParent()->color = NODE_COLOR_BLACK;
            return NULL;
        }
        node_pointer           deleteCase5(node_pointer node){
//            std::cout << "5!!!" << node->parent->data.first << "\n";
            node_pointer s = node->getSibling();
            node_pointer c = node->getCloseNepfew();
            if(node->isLeft()){
                rotateRight(s);
            } else {
                rotateLeft(s);
            }
//            std::cout << "5!!!" << node->parent->data.first << "\n";
            s->color = NODE_COLOR_RED;
            c->color = NODE_COLOR_BLACK;
            return deleteCase6(node);
        }
        node_pointer           deleteCase6(node_pointer node){
//            std::cout << "6!!!" << node->parent->data.first << "\n";
                node->getSibling()->color = node->getParent()->color;
                node->getParent()->color = NODE_COLOR_BLACK;
                node->getDistantNepfew()->color = NODE_COLOR_BLACK;
//            return NULL;
            if(node->isLeft())
                rotateLeft(node->parent);
            else
                rotateRight(node->parent);
            return NULL;
        }
        node_pointer           deleteBalanceLevel(node_pointer  node, int deleteCase){
            switch (deleteCase) {
                case 0 : {
                    return NULL;
                }
                case 2 : {
                    return NULL;
                }
                case 1 : {
                    return deleteCase1(node);
                }
                case 3: {
//                    std::cout << "3!!!" << node->parent->data.first << "\n";
                    node->parent->color = NODE_COLOR_RED;
                    node->getSibling()->color = NODE_COLOR_BLACK;
                    if(node->isLeft())
                        rotateLeft(node->parent);
                    else
                        rotateRight(node->parent);
//                    std::cout << "3!!!" << node->parent->data.first << "\n";
                    if(node->getDistantNepfew() && node->getDistantNepfew()->color) {
                        return deleteCase6(node);
                    } else if(node->getCloseNepfew() && node->getCloseNepfew()->color) {
                        return deleteCase5(node);
                    } else {
                        return deleteCase4(node);
                    }
                }
                case 5 :{
                    return deleteCase5(node);
                }
                case 6: {
                    return deleteCase6(node);
                }
                case 4 : {
                    return deleteCase4(node);
                }
            }
            return NULL;
        }
    };

    template <class Key, class T, class Compare, class Allocator>
    bool operator ==(	const map<Key, T, Compare, Allocator>& x,
                         const map<Key, T, Compare, Allocator>& y)
    {
        return(x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator !=(	const map<Key, T, Compare, Allocator>& x,
                         const map<Key, T, Compare, Allocator>& y)
    {
        return!(x == y);
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator <(	const map<Key, T, Compare, Allocator>& x,
                        const map<Key, T, Compare, Allocator>& y)
    {
        return(ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator >(	const map<Key, T, Compare, Allocator>& x,
                        const map<Key, T, Compare, Allocator>& y)
    {
        return(y < x);
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator >=(	const map<Key, T, Compare, Allocator>& x,
                         const map<Key, T, Compare, Allocator>& y)
    {
        return !(x < y);
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator <=(	const map<Key, T, Compare, Allocator>& x,
                         const map<Key, T, Compare, Allocator>& y)
    {
        return !(y < x);
    }
}
