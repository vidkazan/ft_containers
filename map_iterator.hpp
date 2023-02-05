#pragma once
#include "./utils.hpp"
#include <stdint.h>
#include <cstddef>

namespace ft
{
    template< class node_type>
    class MapIterator : public ft::iterator<ft::bidirectional_iterator_tag, typename node_type::value_type>
    {
    public:
        typedef node_type *																				node_ptr;
        typedef typename node_type::value_type															value_type;
        typedef typename node_type::value_type* 														pointer;
        typedef typename node_type::value_type&															reference;
        typedef const typename node_type::value_type* 													const_pointer;
        typedef const typename node_type::value_type&													const_reference;

        ///CONSTRUCTION

    public:
        MapIterator(node_ptr ptr = NULL) : ptr(ptr), nil_ptr(ptr), first_ptr(ptr) {};
        MapIterator(const MapIterator &copy) : ptr(copy.ptr), nil_ptr(copy.nil_ptr), first_ptr(copy.first_ptr) {};
        MapIterator &operator=(const MapIterator &other)
        {
            ptr = other.ptr;
            nil_ptr = other.nil_ptr;
            first_ptr = other.first_ptr;
            return (*this);
        }

        MapIterator &operator++(void)//pre-increment
        {
            if (ptr == nil_ptr && first_ptr != ptr)
                ptr = first_ptr;
            else if (ptr->right != nil_ptr)
            {
                ptr = ptr->right;
                while (ptr->left != nil_ptr)
                    ptr = ptr->left;
            }
            else
            {
                node_ptr current = ptr;
                node_ptr tmp = ptr;
                if (ptr->parent == NULL)
                {
                    ptr = current->right;
                    return (*this);
                }
                ptr = ptr->parent;
                while (ptr->left != tmp)
                {
                    if (ptr->parent == NULL)
                    {
                        ptr = current->right;
                        break;
                    }
                    tmp = ptr;
                    ptr = ptr->parent;
                }
            }
            return(*this);
        };

        MapIterator &operator--() //pre-decrement
        {
            if (ptr == nil_ptr)
                ptr = ptr->parent;
            else if (ptr->left != nil_ptr)
            {
                ptr = ptr->left;
                while (ptr->right != nil_ptr)
                    ptr = ptr->right;
            }
            else
            {
                node_ptr tmp = ptr;
                ptr = ptr->parent;
                while (ptr->right != tmp)
                {
                    tmp = ptr;
                    if (ptr->parent == NULL)
                    {
                        ptr = tmp->left - 1;
                        break;
                    }
                    ptr = ptr->parent;
                }
            }
            return(*this);
        };

        MapIterator operator++(int) {MapIterator temp(*this); ++(*this); return (temp);} //post-increment
        MapIterator operator--(int) { MapIterator temp(*this); --(*this); return(temp);} //post-decrement
        reference operator*(void) {return *(ptr->value);};
        pointer operator->(void) {return ptr->value;};
        const_reference operator*(void) const {return *(ptr->value);};
        const_pointer operator->(void) const {return ptr->value;};

        node_ptr getPtr(void) const
        {return (ptr);}

        node_ptr getNilPtr(void) const
        {return (nil_ptr);}

        node_ptr getFirstPtr(void) const
        {return (first_ptr);}

    private:
        node_ptr ptr;
        node_ptr nil_ptr;
        node_ptr first_ptr;
    };

    template< class node_type>
    class const_MapIterator : public ft::iterator<ft::bidirectional_iterator_tag, typename node_type::value_type>
    {
    public:
        typedef node_type *																				node_ptr;
        typedef const typename node_type::value_type													value_type;
        typedef typename node_type::value_type* 														pointer;
        typedef typename node_type::value_type&															reference;
        typedef const typename node_type::value_type* 													const_pointer;
        typedef const typename node_type::value_type&													const_reference;



        ///CONSTRUCTION
        const_MapIterator(node_ptr ptr = NULL) : ptr(ptr), nil_ptr(ptr), first_ptr(ptr) {};
        const_MapIterator(node_ptr ptr, node_ptr first_element, node_ptr last_element) : ptr(ptr), nil_ptr(last_element), first_ptr(first_element){};
        const_MapIterator(const const_MapIterator &copy) : ptr(copy.ptr), nil_ptr(copy.nil_ptr), first_ptr(copy.first_ptr) {};
        const_MapIterator(const ft::MapIterator<node_type> &copy) : ptr(copy.getPtr()), nil_ptr(copy.getNilPtr()), first_ptr(copy.getFirstPtr()) {};
        const_MapIterator &operator=(const const_MapIterator &other)
        {
            ptr = other.ptr;
            nil_ptr = other.nil_ptr;
            first_ptr = other.first_ptr;
            return (*this);
        }
        const_MapIterator &operator=(const ft::MapIterator<node_type> &other)
        {
            ptr = other.getPtr();
            nil_ptr = other.getNilPtr();
            first_ptr = other.getFirstPtr();
            return (*this);
        }

        const_MapIterator &operator++(void)	//pre-increment
        {
            if (ptr == nil_ptr && first_ptr != ptr)
                ptr = first_ptr;
            else if (ptr->right != nil_ptr)
            {
                ptr = ptr->right;
                while (ptr->left != nil_ptr)
                    ptr = ptr->left;
            }
            else
            {
                node_ptr current = ptr;
                node_ptr tmp = ptr;
                if (ptr->parent == NULL)
                {
                    ptr = current->right;
                    return (*this);
                }
                ptr = ptr->parent;
                while (ptr->left != tmp)
                {
                    if (ptr->parent == NULL)
                    {
                        ptr = current->right;
                        break;
                    }
                    tmp = ptr;
                    ptr = ptr->parent;
                }
            }
            return(*this);
        };

        const_MapIterator &operator--()	//pre-decrement
        {
            if (ptr == nil_ptr)
                ptr = ptr->parent;
            else if (ptr->left != nil_ptr)
            {
                ptr = ptr->left;
                while (ptr->right != nil_ptr)
                    ptr = ptr->right;
            }
            else
            {
                node_ptr tmp = ptr;
                ptr = ptr->parent;
                while (ptr->right != tmp)
                {
                    tmp = ptr;
                    if (ptr->parent == NULL)
                    {
                        ptr = tmp->left - 1;
                        break;
                    }
                    ptr = ptr->parent;
                }
            }
            return(*this);
        };

        const_MapIterator operator++(int) {const_MapIterator temp(*this); ++(*this); return (temp);} //post-increment
        const_MapIterator operator--(int) {const_MapIterator temp(*this); --(*this); return(temp);} //post-decrement
        reference operator*(void) {return *(ptr->value);};
        pointer operator->(void) {return ptr->value;};
        const_reference operator*(void) const {return *(ptr->value);};
        const_pointer operator->(void) const {return ptr->value;};

        node_ptr getPtr(void) const
        {return (ptr);}

    private:
        node_ptr ptr;
        node_ptr nil_ptr;
        node_ptr first_ptr;
    };
}