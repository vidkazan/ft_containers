//
// Created by Dmitrii Grigorev on 29.04.22.
//
#pragma once
#include "utils.hpp"
#include <iostream>
#include "./map.hpp"
#include "./map_iterator.hpp"
#include "./pair.hpp"
#include "./reverse_iterator.hpp"

namespace ft {
	template<class Key, class Compare = std::less<Key>,
            class Allocator = std::allocator<Key> >
    class set {
    	public:
			typedef             Key 									                key_type;
			typedef             Key					                					value_type;
			typedef             size_t                                                  size_type;
			typedef             ptrdiff_t                                               difference_type;
			typedef             Compare									                key_compare;
			typedef             Compare									                value_compare;
			typedef             Allocator                               	            allocator_type;
			typedef typename    Allocator::reference      			                    reference;
			typedef typename    Allocator::const_reference			                    const_reference;
			typedef typename    Allocator::pointer        			                    pointer;
			typedef typename    Allocator::const_pointer  			                    const_pointer;
			typedef             node<value_type>                                        node_type;
			typedef             map_iterator<node_type>					                iterator;
			typedef             const_map_iterator<node_type>				            const_iterator;
			typedef             ft::reverse_iterator<iterator>							reverse_iterator;
			typedef             ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef             node_type*                                              node_pointer;
			typedef typename    allocator_type::template rebind<ft::node<value_type> >::other	node_allocator_type;

			explicit				set(
										const key_compare &comp = key_compare(),
										const allocator_type &alloc = allocator_type()
									);
									set(const set& x);
									~set();
			set &operator=(const set& other)
			{
				this->clear();
				_node_allocator.deallocate(_leaf,1);
				createLeafNode();
				const_iterator it_begin = other.begin();
				const_iterator it_end = other.end();
				while(it_begin != it_end)
				{
					this->insert(*it_begin);
					it_begin++;
				}
				return(*this);
			}
			template <class InputIterator>
									set (InputIterator first,	InputIterator last);

			allocator_type          get_allocator() const;
			bool                    empty() const;
			size_type               size() const;
			size_type               max_size() const;
			pair<iterator, bool>    insert(const value_type& x);
			iterator				insert (iterator position, const value_type& value);
			template< class InputIt >
			void    				insert( InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type* = nullptr);
			size_type       		erase(const key_type& k);
			void					erase( iterator pos );
			void					erase( iterator first, iterator last );
			iterator        		find(const key_type& x);
			const_iterator  		find(const key_type& x) const;;
			iterator       			lower_bound (const key_type& key);
			const_iterator  		lower_bound (const key_type& key) const;
			iterator        		upper_bound (const key_type& key);
			const_iterator  		upper_bound (const key_type& key) const;
			key_compare     		key_comp() const;
			value_compare   		value_comp() const;
			pair<iterator,iterator>             equal_range (const key_type& key);
			pair<const_iterator,const_iterator> equal_range (const key_type& key) const;
			size_type       		count( const Key& key ) const;
			iterator        		begin();
			const_iterator  		begin() const;
			iterator        		end();
			const_iterator  		end() const;
			void            		clear();
			void					swap (set& x);
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;

        private:
            node_pointer    	    _root;
            node_pointer            _leaf;
            size_type			    _size;
            node_allocator_type     _node_allocator;
            allocator_type          _allocator;
            key_compare             _cmp;

			void            		updateLeafParent();
			node_pointer    		findPointer(const key_type& x);
			node_pointer    		findPointer(const key_type& x) const;;
			void            		swap_4_replacing_in_children(node_pointer a, node_pointer b);
			void            		swap_3_replacing_children(node_pointer a, node_pointer b, node_pointer ap, node_pointer bp);
			void            		swap_2_replacing_parents(node_pointer a, node_pointer b, node_pointer ap, node_pointer bp);
			void            		swap_1_replacing_in_parents(node_pointer a, node_pointer b);
			void            		swap(node_pointer a, node_pointer b);
			void            		deleteMeFromParent(node_pointer me);
			void            		replaceMeFromParent(node_pointer me, node_pointer replacement);
			void            		createLeafNode();
			node_pointer    		createNode(const value_type& x, node_pointer parent);
			node_pointer    		insertEntry(const value_type& x);
			node_pointer    		rotateLeft(const node_pointer root);
			node_pointer    		rotateRight(const node_pointer root);
			node_pointer    		balanceInsert(int insertCase,node_pointer node);
			void            		deleteNode(node_pointer node);
			ft::pair<iterator,bool>	insertStore(const value_type& x);
			node_pointer    		getSuccessor(node_pointer node);
			bool            		replaceBySuccessor(node_pointer node);
			bool            		eraseStore(const key_type& k);
			void            		balanceDelete(node_pointer node);
			node_pointer          	deleteCase1(node_pointer node);
			node_pointer          	deleteCase4(node_pointer node);
			node_pointer           	deleteCase5(node_pointer node);
			node_pointer           	deleteCase6(node_pointer node);
			node_pointer           	deleteBalanceLevel(node_pointer  node, int deleteCase);
			node_pointer 			getParent(node_pointer p);
			node_pointer 			getSibling(node_pointer p);
			node_pointer 			getCloseNepfew(node_pointer p);
			node_pointer 			getDistantNepfew(node_pointer p);
			node_pointer 			getGrandfather(node_pointer p);
			node_pointer 			getUncle(node_pointer p);
			bool 					isEqualKeys(const key_type& a,const key_type& b) const;
			bool 					isLessKey(const key_type& a,const key_type& b) const;
			bool 					isBiggerKey(const key_type& a,const key_type& b) const;
    };

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::allocator_type
	set<Key,Compare,Allocator>::get_allocator() const {return _allocator;}

	template <class Key, class Compare, class Allocator>
	bool set<Key,Compare,Allocator>::empty() const {
		if(_root != NULL)
			return false;
		return true;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::size_type
	set<Key,Compare,Allocator>::size() const {
		return _size;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::size_type
	set<Key,Compare,Allocator>::max_size() const {
		return (_node_allocator.max_size());
	}

	template <class Key, class Compare, class Allocator>
	pair<typename ft::set<Key,Compare,Allocator>::iterator, bool>
	set<Key,Compare,Allocator>::insert(const set::value_type &x) {
		return (insertStore(x));
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::iterator
	set<Key,Compare,Allocator>::insert(set::iterator position, const set::value_type &value) {
		static_cast<void>(position);
		return (insertStore(value).first);
	}

	template <class Key, class Compare, class Allocator>
	template<class InputIt>
	void set<Key,Compare,Allocator>::insert(InputIt first, InputIt last,
												 typename enable_if<!is_integral<InputIt>::value>::type *) {
		for (; first != last; first++) {
			insertStore(*first);
		}
	}

	template <class Key, class Compare, class Allocator>
	set<Key,Compare,Allocator>::set(const key_compare &comp, const allocator_type &alloc)
			:_root(NULL),_size(0),_allocator(alloc),_cmp(comp) {
		createLeafNode();
	}

	template <class Key, class Compare, class Allocator>
	set<Key,Compare,Allocator>::set(const set &x) :_root(NULL),_leaf(NULL), _size(0) {
		createLeafNode();
		const_iterator it_begin = x.begin();
		const_iterator it_end = x.end();
		while(it_begin != it_end)
		{
			this->insert(*it_begin);
			it_begin++;
		}
	}

	template <class Key, class Compare, class Allocator>
	set<Key,Compare,Allocator>::~set() {
		this->clear();
		_node_allocator.deallocate(_leaf,1);
	}

	template <class Key, class Compare, class Allocator>
	template<class InputIterator>
	set<Key,Compare,Allocator>::set(InputIterator first, InputIterator last) : _root(NULL), _leaf(NULL), _size(0) {
		createLeafNode();
		while(first != last)
		{
			insert(*first);
			first++;
		}
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::size_type
	set<Key,Compare,Allocator>::erase(const key_type &k) {
		int res =  eraseStore(k) ? 1 : 0;
		updateLeafParent();
		return res;
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::erase(set::iterator pos) {
		eraseStore(*pos);
		updateLeafParent();
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::erase(set::iterator first, set::iterator last) {
		iterator temp = first;
		while(first != last)
		{
			first++;
			eraseStore(*temp);
			temp = first;
		}
		updateLeafParent();
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::iterator
	set<Key,Compare,Allocator>::find(const key_type &x) {
		node_pointer current = _root;
		while(current && current->data) {
			if(isEqualKeys(x,*current->data))
				return iterator(current, this->begin().getPtr(), _leaf);
			if(isLessKey(x, *current->data)) {
				current = current->left;
			} else {
				current = current->right;
			}
		}
		return end();
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::const_iterator
	set<Key,Compare,Allocator>::find(const key_type &x) const {
		node_pointer current = _root;
		while(current && current->data) {
			if(isEqualKeys(x,*current->data))
				return const_iterator(current, this->begin().getPtr(), _leaf);
			if(isLessKey(x, *current->data)) {
				current = current->left;
			} else {
				current = current->right;
			}
		}
		return end();
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::iterator
	set<Key,Compare,Allocator>::lower_bound(const key_type &key) {
		iterator it = this->begin();
		iterator end = this->end();
		while(it != end && key_comp()(*it, key))
			it++;
		return (it);
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::const_iterator
	set<Key,Compare,Allocator>::lower_bound(const key_type &key) const {
		const_iterator it = this->begin();
		const_iterator end = this->end();
		while(it != end && key_comp()(*it, key))
			it++;
		return (it);
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::iterator
	set<Key,Compare,Allocator>::upper_bound(const key_type &key) {
		iterator it = this->begin();
		iterator end = this->end();
		while(it != end && !key_comp()(key, *it))
			it++;
		return (it);
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::const_iterator
	set<Key,Compare,Allocator>::upper_bound(const key_type &key) const {
		const_iterator it = begin();
		const_iterator end = end();
		while(it != end && !key_comp()(key, *it))
			it++;
		return (it);
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::key_compare
	set<Key,Compare,Allocator>::key_comp() const {
		return (_cmp);
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::value_compare
	set<Key,Compare,Allocator>::value_comp() const {
		return value_compare(_cmp);
	}

	template <class Key, class Compare, class Allocator>
	pair<typename ft::set<Key,Compare,Allocator>::iterator, typename ft::set<Key,Compare,Allocator>::iterator>
	set<Key,Compare,Allocator>::equal_range(const key_type &key) {
		return (ft::make_pair(lower_bound(key), upper_bound(key)));
	}

	template <class Key, class Compare, class Allocator>
	pair<typename ft::set<Key,Compare,Allocator>::const_iterator, typename ft::set<Key,Compare,Allocator>::const_iterator>
	set<Key,Compare,Allocator>::equal_range(const key_type &key) const {
		return (ft::make_pair(lower_bound(key), upper_bound(key)));
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::size_type
	set<Key,Compare,Allocator>::count(const Key &key) const {
		if (findPointer(key) == _leaf)
			return (0);
		return (1);
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::iterator
	set<Key,Compare,Allocator>::begin() {
		if(!_root){
			return iterator(_leaf,_leaf,_leaf);
		}
		node_pointer node = this->_root;
		while(node->left != _leaf){
			node = node->left;
		}
		return iterator(node,node,_leaf);
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::const_iterator
	set<Key,Compare,Allocator>::begin() const {
		if(!_root){
			return iterator(_leaf,_leaf,_leaf);
		}
		node_pointer node = this->_root;
		while(node->left != _leaf){
			node = node->left;
		}
		return const_iterator(node,node,_leaf);
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::iterator
	set<Key,Compare,Allocator>::end() {
		if(!_root){
			return iterator(_leaf,_leaf,_leaf);
		}
		return iterator(_leaf, this->begin().getPtr(),_leaf);
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::const_iterator
	set<Key,Compare,Allocator>::end() const {
		if(!_root){
			return iterator(_leaf,_leaf,_leaf);
		}
		return const_iterator(_leaf, this->begin().getPtr(),_leaf);
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::clear() {
		erase(this->begin(), this->end());
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::swap(set &x) {
		node_pointer l = x._leaf;
		node_pointer r = x._root;
		size_type s = x._size;
		x._leaf = _leaf;
		x._root = _root;
		x._size = _size;
		_leaf = l;
		_root = r;
		_size = s;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::reverse_iterator
	set<Key,Compare,Allocator>::rbegin() {
		return reverse_iterator(this->end());
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::const_reverse_iterator
	set<Key,Compare,Allocator>::rbegin() const {
		return const_reverse_iterator(this->end());
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::reverse_iterator
	set<Key,Compare,Allocator>::rend() {
		return reverse_iterator(this->begin());
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::const_reverse_iterator
	set<Key,Compare,Allocator>::rend() const {
		return const_reverse_iterator(this->begin());
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::updateLeafParent() {
		node_pointer tmp = _root;
		while(tmp && tmp->right && tmp->right->data) {
			tmp = tmp->right;
		}
		if(_leaf)
			_leaf->parent = tmp;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::findPointer(const key_type &x) {
		node_pointer current = _root;
		while(current != NULL && current->data) {
			if(isEqualKeys(x,*current->data))
				return current;
			if(isLessKey(x, *current->data)) {
				current = current->left;
			} else {
				current = current->right;
			}
		}
		return _leaf;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::findPointer(const key_type &x) const {
		node_pointer current = _root;
		while(current != NULL && current->data) {
			if(isEqualKeys(x,*current->data))
				return current;
			if(isLessKey(x, *current->data)) {
				current = current->left;
			} else {
				current = current->right;
			}
		}
		return _leaf;
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::swap_4_replacing_in_children(set::node_pointer a, set::node_pointer b) {
		a->left->parent = a;
		a->right->parent = a;
		b->left->parent = b;
		b->right->parent = b;
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::swap_3_replacing_children(set::node_pointer a, set::node_pointer b,
																	set::node_pointer ap, set::node_pointer bp) {
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

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::swap_2_replacing_parents(set::node_pointer a, set::node_pointer b,
																   set::node_pointer ap, set::node_pointer bp) {
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

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::swap_1_replacing_in_parents(set::node_pointer a, set::node_pointer b) {
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

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::swap(set::node_pointer a, set::node_pointer b) {
		node_pointer ap,bp;
		ap = a->parent;
		bp = b->parent;
		swap_1_replacing_in_parents(a,b);
		swap_2_replacing_parents(a,b,ap,bp);
		swap_3_replacing_children(a,b,ap,bp);
		swap_4_replacing_in_children(a,b);
		ft::swap(a->color,b->color);
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::deleteMeFromParent(set::node_pointer me) {
		if(!me->parent)
			return;
		if(me == me->parent->left) {
			me->parent->left = _leaf;
		} else {
			me->parent->right = _leaf;
		}
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::replaceMeFromParent(set::node_pointer me, set::node_pointer replacement) {
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

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::createLeafNode() {
		_leaf = _node_allocator.allocate(1);
		_leaf->color = NODE_COLOR_BLACK;
		_leaf->parent = NULL;
		_leaf->left = NULL;
		_leaf->right = NULL;
		_leaf->data = NULL;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::createNode(const set::value_type &x, set::node_pointer parent) {
		node_pointer node  = _node_allocator.allocate(1);
		node->color = NODE_COLOR_RED;
		node->left = _leaf;
		node->right = _leaf;
		node->parent = parent;
		node->data = _allocator.allocate(1);
		_allocator.construct(node->data,x);
		return node;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::insertEntry(const set::value_type &x) {
		node_pointer current = _root;
		node_pointer previous = _root->parent;
		while(current != _leaf) {
			previous = current;
			if(isLessKey(x,*current->data)) {
				current = current->left;
			} else {
				current = current->right;
			}
		}
		if(isBiggerKey(*previous->data, x)) {
			previous->left = createNode(x, previous);
			return previous->left;
		} else {
			previous->right = createNode(x, previous);
			return previous->right;
		}
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::rotateLeft(set::node_pointer const root) {
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

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::balanceInsert(int insertCase, set::node_pointer node) {
		switch (insertCase) {
			case 0:
				return NULL;
			case 1: {
				return NULL;
			}
			case 2: {
				node->parent->color       = NODE_COLOR_BLACK;
				getGrandfather(node)->color  = NODE_COLOR_RED;
				getUncle(node)->color        = NODE_COLOR_BLACK;
				node = node->parent;
				break;
			}
			case 3: {
				return NULL;
			}
			case 4: {
				node->parent->color = NODE_COLOR_BLACK;
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

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::rotateRight(set::node_pointer const root) {
		node_pointer newRoot, newRight,b;
		newRoot = root->left;
		newRight = root;
		b = newRoot->right;
		if(!root->parent){
			_root = newRoot;
		} else if(root->isLeft()){
			root->parent->left = newRoot;
		} else if(root->isRight()){
			root->parent->right = newRoot;
		}
		newRoot->parent = root->parent;
		newRoot->right = newRight;
		newRight->parent = newRoot;
		if(b!= _leaf)
			b->parent = newRight;
		newRight->left = b;
		return newRoot;
	}

	template <class Key, class Compare, class Allocator>
	pair<typename ft::set<Key,Compare,Allocator>::iterator, bool> set<Key,Compare,Allocator>::insertStore(const set::value_type &x) {
		node_pointer p = findPointer(x);
		if(findPointer(x) != _leaf) {
			return (ft::make_pair<iterator,bool>(iterator(p, this->begin().getPtr(),_leaf), false));
		}
		if(this->empty()) {
			_root = createNode(x, NULL);
			_root->color = NODE_COLOR_BLACK;
			_size++;
			updateLeafParent();
			return (ft::make_pair<iterator,bool>(iterator(_root, _root,_leaf), true));
		}
		_size++;
		node_pointer place = insertEntry(x);
		node_pointer res = place;
		int         insertCase = 0;
		while(place != NULL) {
			if(place->parent \
                && place->parent->isBlack()) {                               //  Insert case 1   Parent is BLACK
				insertCase = 1;
			}
			else if(getGrandfather(place)
					&& place->parent->isRed() \
                     && getUncle(place)->isRed() \
                     && getGrandfather(place)->isBlack()) {                      //  Insert case 2   Parent && Uncle is RED && Grand is BLACK
				insertCase = 2;
			}
			else if((!place->parent && place->color == NODE_COLOR_RED)) {
				place->color = NODE_COLOR_BLACK;
				insertCase = 3;
			}
			else if(!place->parent) {
				insertCase = 1;
			}
			else if(place->parent && place->parent->isRed() && !getGrandfather(place)) { //  Insert case 4   Parent is RED && no Grand
				insertCase = 4;
			}
			else if(getUncle(place) && place->parent->isRed() \
                                          && getUncle(place)->isBlack() \
                                          && getGrandfather(place)->isBlack()) { //  Insert case 5   Parent is RED && Uncle BLACK && Grand BLACK &&
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
			if(insertCase == 60 || insertCase == 61 || insertCase == 50 || insertCase == 51) {
				updateLeafParent();
				return (ft::make_pair<iterator,bool>(iterator(res, this->begin().getPtr(),_leaf), true));
			}
		}
		updateLeafParent();
		return (ft::make_pair<iterator,bool>(iterator(res, this->begin().getPtr(),_leaf), true));
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::getSuccessor(set::node_pointer node) {
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

	template <class Key, class Compare, class Allocator>
	bool set<Key,Compare,Allocator>::replaceBySuccessor(set::node_pointer node) {

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

	template <class Key, class Compare, class Allocator>
	bool set<Key,Compare,Allocator>::eraseStore(const key_type &k) {
		if(findPointer(k) == _leaf) {
			return false;
		}
		node_pointer node = findPointer(k);
		if(!node->parent && node->left == _leaf && node->right == _leaf) {
			deleteMeFromParent(node);
			deleteNode(node);
			_root = NULL;
			return true;
		} else if(node->color == NODE_COLOR_RED && (node->left == _leaf && node->right == _leaf)) {
			deleteMeFromParent(node);
			deleteNode(node);
			return true;
		} else if((node->left == _leaf && node->right != _leaf) || (node->left != _leaf && node->right == _leaf)) {
			if (node->left != _leaf) {
				swap(node, node->left);
				replaceMeFromParent(node, node->left);
			} else {
				swap(node, node->right);
				replaceMeFromParent(node, node->right);
			}
			deleteNode(node);
		} else if(node->color == NODE_COLOR_BLACK && (node->left == _leaf && node->right == _leaf)) {
			_leaf->parent = node->parent;
			node_pointer startBalance = _leaf;
			deleteMeFromParent(node);
			deleteNode(node);
			balanceDelete(startBalance);
		} else if(node->left != _leaf && node->right != _leaf) {
			node_pointer balanceStart;
			balanceStart = _leaf;
			bool deletedBlack = replaceBySuccessor(node);
			_leaf->parent = node->parent;
			if(deletedBlack) {
				balanceDelete(balanceStart);
			}
		}
		return true;
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::deleteNode(set::node_pointer node) {
		_allocator.deallocate(node->data,1);
		_node_allocator.destroy(node);
		_node_allocator.deallocate(node,1);
		_size--;
	}

	template <class Key, class Compare, class Allocator>
	void set<Key,Compare,Allocator>::balanceDelete(set::node_pointer node) {
		while(node != NULL) {
			int deleteCase = 0;
			if(getSibling(node) && getSibling(node)->color) {
				deleteCase = 3;
			} else if (getDistantNepfew(node) && getDistantNepfew(node)->color) {
				deleteCase = 6;
			} else if(getCloseNepfew(node) && getCloseNepfew(node)->color) {
				deleteCase = 5;
			} else if(node->parent && node->parent->color) {
				deleteCase = 4;
			} else if (node->parent && !node->parent->color && getSibling(node) && !getSibling(node)->color &&
					   getCloseNepfew(node) && getDistantNepfew(node) && !getCloseNepfew(node)->color &&
					   !getDistantNepfew(node)->color) {
				deleteCase = 1;
			} else if (!node->parent) {
				deleteCase = 2;
			}
			node = deleteBalanceLevel(node, deleteCase);
		}
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::deleteCase1(set::node_pointer node) {
		getSibling(node)->color = NODE_COLOR_RED;
		return node->parent;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::deleteCase4(set::node_pointer node) {
		getSibling(node)->color = NODE_COLOR_RED;
		getParent(node)->color = NODE_COLOR_BLACK;
		return NULL;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::deleteCase5(set::node_pointer node) {
		node_pointer s = getSibling(node);
		node_pointer c = getCloseNepfew(node);
		if(node->isLeft()){
			rotateRight(s);
		} else {
			rotateLeft(s);
		}
		s->color = NODE_COLOR_RED;
		c->color = NODE_COLOR_BLACK;
		return deleteCase6(node);
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::deleteCase6(set::node_pointer node) {
		getSibling(node)->color = getParent(node)->color;
		getParent(node)->color = NODE_COLOR_BLACK;
		getDistantNepfew(node)->color = NODE_COLOR_BLACK;
		if(node->isLeft())
			rotateLeft(node->parent);
		else
			rotateRight(node->parent);
		return NULL;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::getParent(set::node_pointer p) {
		return p->parent;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::deleteBalanceLevel(set::node_pointer node, int deleteCase) {
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
				node->parent->color = NODE_COLOR_RED;
				getSibling(node)->color = NODE_COLOR_BLACK;
				if(node->isLeft())
					rotateLeft(node->parent);
				else
					rotateRight(node->parent);
				if(getDistantNepfew(node) && getDistantNepfew(node)->color) {
					return deleteCase6(node);
				} else if(getCloseNepfew(node) && getCloseNepfew(node)->color) {
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

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::getSibling(set::node_pointer p) {
		if(p->parent) {
			if(p->parent->left == p) {
				return p->parent->right;
			} else {
				return p->parent->left;
			}
		}
		return NULL;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::getCloseNepfew(set::node_pointer p) {
		if(!this->getSibling(p)) {
			return NULL;
		}
		return p->isLeft() ? this->getSibling(p)->left : this->getSibling(p)->right;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::getDistantNepfew(set::node_pointer p) {
		if(!getSibling(p)) {
			return NULL;
		}
		return p->isLeft() ? this->getSibling(p)->right : this->getSibling(p)->left;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::getGrandfather(set::node_pointer p) {
		if(p->parent && p->parent->parent)
			return p->parent->parent;
		return NULL;
	}

	template <class Key, class Compare, class Allocator>
	typename ft::set<Key,Compare,Allocator>::set::node_pointer
	set<Key,Compare,Allocator>::getUncle(set::node_pointer p) {
		if(!p->parent || !p->parent->parent)
			return NULL;
		if(isLessKey(*p->parent->data,*p->parent->parent->data)) {

			return p->parent->parent->right;
		} else {
			return p->parent->parent->left;
		}
	}

	template <class Key, class Compare, class Allocator>
	bool set<Key,Compare,Allocator>::isEqualKeys(const key_type &a, const key_type &b) const {
		if(key_comp()(a,b)  || key_comp()(b,a))
			return false;
		return true;
	}

	template <class Key, class Compare, class Allocator>
	bool set<Key,Compare,Allocator>::isLessKey(const key_type &a, const key_type &b) const {
		return (key_comp()(a,b));
	}

	template <class Key, class Compare, class Allocator>
	bool set<Key,Compare,Allocator>::isBiggerKey(const key_type &a, const key_type &b) const {
		return (!isLessKey(a,b) && !isEqualKeys(a,b));
	}

	template <class Key, class Compare, class Allocator>
    bool operator ==(	const set<Key,Compare,Allocator>& x,
                         const set<Key,Compare,Allocator>& y)
    {
        return(x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
    }

    template <class Key, class Compare, class Allocator>
    bool operator !=(	const set<Key,Compare,Allocator>& x,
                         const set<Key,Compare,Allocator>& y)
    {
        return!(x == y);
    }

    template <class Key, class Compare, class Allocator>
    bool operator <(	const set<Key,Compare,Allocator>& x,
                        const set<Key,Compare,Allocator>& y)
    {
        return(ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
    }

    template <class Key, class Compare, class Allocator>
    bool operator >(	const set<Key,Compare,Allocator>& x,
                        const set<Key,Compare,Allocator>& y)
    {
        return(y < x);
    }

    template <class Key, class Compare, class Allocator>
    bool operator >=(	const set<Key,Compare,Allocator>& x,
                         const set<Key,Compare,Allocator>& y)
    {
        return !(x < y);
    }

    template <class Key, class Compare, class Allocator>
    bool operator <=(	const set<Key,Compare,Allocator>& x,
                         const set<Key,Compare,Allocator>& y)
    {
        return !(y < x);
    }
}
