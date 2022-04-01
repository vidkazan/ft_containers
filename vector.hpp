#pragma once
#include <iostream>
#include <memory>
#include <cmath>
namespace ft
{
    class IteratorVector{

    };

    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
    public:
        typedef          T                               value_type;
        typedef          Allocator                       allocator_type;
        typedef          size_t                          size_type;
        typedef          ptrdiff_t                       difference_type;

        // random access iterator to value type
        // const iterator to value type
        // reverse iterator to value type

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

//    private:
    private:
        allocator_type  _alloc;
        pointer      _vector;
        size_type    _size;
        size_type    _capacity;

    public:
        class iterator{

        };
        class const_iterator{

        };
        class const_reverse_iterator{

        };
//        Constructors

//        1) Default constructor. Constructs an empty container with a default-constructed allocator.
//        2) Constructs an empty container with the given allocator alloc.
        explicit         vector( const allocator_type& alloc = allocator_type())
                        : _alloc(alloc), _capacity(0), _size(0)
        {
            _vector = _alloc.allocate(_capacity);
        };
//        3) Constructs the container with count copies of elements with value value.
        explicit vector (size_type count, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type())
                                 : _size(count), _alloc(alloc), _capacity(count)
        {
            _vector = _alloc.allocate(_capacity);
            for(size_type i=0;i<_size;i++){
                _alloc.construct(&_vector[i], val);
            }
        };
//        5) Constructs the container with the contents of the range [first, last).
//        template <class InputIterator>
//        vector (InputIterator first, InputIterator last,
//                const allocator_type& alloc = allocator_type()) : _alloc(alloc)
//        {
//            int i = 0;
//            InputIterator pos = first;
//            for(;pos!=last;pos++){
//                i++;
//            }
//            _capacity = i;
//            _size = i;
//            _vector = _alloc.allocate(_capacity);
//            pos = first;
//            for(i=0;i!=_size-1;i++)
//            {
//                _alloc.construct(&_vector[i],*pos);
//                if(pos==last)
//                    break;
//                pos++;
//            }
//        };
//        6) Copy constructor. Constructs the container with the copy of the contents of other.
        vector( const vector& other ){};
//        Destructors
        ~vector(){
              this->clear();
              _alloc.deallocate(_vector, _capacity);
          };
        template <class InputIt>
        void                    assign(InputIt first, InputIt last){};
        void                    assign(size_type n, const value_type& val){};
        reference               at(size_type n)
        {
            if(n < _size)
                return _vector[n];
            throw std::out_of_range("ft::vector.at() out of range");
        };
        const_reference         at(size_type n) const
        {
            if(n <= _size - 1)
                return _vector[n];
            throw std::out_of_range("ft::vector.at() out of range");
        };
        reference               front()
        {
            if(_size)
                return _vector[0];
        };
        const_reference         front() const
        {
            if(_size)
                return _vector[0];
        };
        reference               back()
        {
            if(_size)
                return _vector[_size-1];
        };
        const_reference         back() const
        {
            if(_size)
                return _vector[_size-1];
        };
        iterator                begin(){};
        const_iterator          begin() const{};
        iterator                end(){};
        const_iterator          end() const{};
        iterator                erase (iterator position){};
        iterator                erase (iterator first, iterator last){};
        size_type               capacity() const{return _capacity;};
        void                    clear()
        {
            for(size_type i=0;i<_size;i++){
                _alloc.destroy(&_vector[i]);
            }
            _size = 0;
        };
        bool                    empty() const{return _size == 0;};
        allocator_type          get_allocator() const{return _alloc;};
        iterator                insert(iterator pos, const value_type& val){};
        void                    insert(iterator pos, size_type n, const value_type& val){};
//        template <class InputIt>
//        void                    insert(iterator pos, InputIt first, InputIt last){};
//        reverse_iterator        rbegin(){};
//        const_reverse_iterator  rbegin() const{};
//        reverse_iterator        rend(){};
//        const_reverse_iterator  rend() const{};
        size_type               max_size() const{return _alloc.max_size();};
        vector&                 operator=(const vector& rhs){};
        reference               operator[](size_type n){return _vector[n];};
        const_reference         operator[](size_type n) const{return _vector[n];};
        void                    pop_back()
        {
            if(_size == 0)
                return;
            _alloc.destroy(&_vector[_size - 1]);
            _size-=1;
        };
        void                    push_back(const value_type& val)
        {
            if((_size + 1) > _capacity)
                reserve(_capacity * 1.5);
            _alloc.construct(&_vector[_size],val);
            _size++;

        };
        void                    reserve (size_type n)
        {
            if(n <= _capacity)
                return;
            if(n > this->max_size())
                throw std::length_error("vector: resize: length > max_size");
            reallocateWithoutNewAssing(n);
        };
        void                    resize (size_type n, value_type val = value_type())
        {
            if(n > this->max_size())
                throw std::length_error("vector: resize: length > max_size");
            if(n > _capacity)
            {
                reallocateWithNewAssign(n, val);
            }
            else if (n < _size)
            {
                for(size_type i=n;i!=_size;i++){
                    _alloc.destroy(&_vector[i]);
                }
                _size = n;
            }
            else
            {
                for(size_type i=(_size - 1);i!=n;i++){
                    _alloc.construct(&_vector[i], val);
                }
                _size = n;
            }
        };
        size_type               size() const{return _size;};
        void                    swap (vector& x)
        {
            //                                          copy _vector -> tmp && reset _vector
            size_type tmp_size = _size;
            size_type tmp_capacity = _capacity;
            pointer tmp = _alloc.allocate(_capacity);
            for(size_type i=0;i<_size;i++)
            {
                _alloc.construct(&tmp[i], _vector[i]);
                _alloc.destroy(&_vector[i]);
            }
            _alloc.deallocate(_vector, _capacity);
            _size = 0;
            _capacity = 0;

            //                                          copy x -> vector && reset x
            _size = x.size();
            _capacity = x.capacity();
            _vector = _alloc.allocate(_capacity);
            for(size_type i=0;i<x._size;i++)
            {
                _alloc.construct(&_vector[i], x[i]);
                _alloc.destroy(&x[i]);
            }
            _alloc.deallocate(x._vector, x._capacity);
            x._size = 0;
            x._capacity = 0;

            //                                          copy tmp -> x && reset tmp
            x._size = tmp_size;
            x._capacity = tmp_capacity;
            _alloc.allocate(x._capacity);
            for(size_type i=0;i<x._size;i++)
            {
                _alloc.construct(&tmp[i], tmp[i]);
                _alloc.destroy(&tmp[i]);
            }
            _alloc.deallocate(tmp, tmp_capacity);
            tmp_capacity = 0;
            tmp_size = 0;
        };
    protected:
        void reallocateWithNewAssign(size_type n, value_type val)
        {
            pointer newVector = _alloc.allocate(n);
            for(size_type i=0;i<_size;i++)
            {
                _alloc.construct(&newVector[i], _vector[i]);
                _alloc.destroy(&_vector[i]);
            }
            _alloc.deallocate(_vector, _capacity);
            for(size_type i=_size;i<n;i++)
            {
                _alloc.construct(&newVector[i], val);
            }
            _vector = newVector;
            _size = n;
            _capacity = n;
        }
        void reallocateWithoutNewAssing(size_type n)
        {
            pointer newVector = _alloc.allocate(n);
            for(size_type i=0;i<_size;i++)
            {
                _alloc.construct(&newVector[i], _vector[i]);
                _alloc.destroy(&_vector[i]);
            }
            _alloc.deallocate(_vector, _capacity);
            _vector = newVector;
            _capacity = n;
        }
    };
}

template <class T, class Alloc>
void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
{
    //                                          copy _vector -> tmp && reset _vector // x -> tmp && reset x
    size_type tmp_size = _size;
    size_type tmp_capacity = _capacity;
    pointer tmp = _alloc.allocate(_capacity);
    for(size_type i=0;i<_size;i++)
    {
        _alloc.construct(&tmp[i], _vector[i]);
        _alloc.destroy(&_vector[i]);
    }
    _alloc.deallocate(_vector, _capacity);
    _size = 0;
    _capacity = 0;

    //                                          copy x -> vector && reset x // y -> x && reset y
    _size = x.size();
    _capacity = x.capacity();
    _vector = _alloc.allocate(_capacity);
    for(size_type i=0;i<x._size;i++)
    {
        _alloc.construct(&_vector[i], x[i]);
        _alloc.destroy(&x[i]);
    }
    _alloc.deallocate(x._vector, x._capacity);
    x._size = 0;
    x._capacity = 0;

    //                                          copy tmp -> x && reset tmp // tmp -> y && reset tmp
    x._size = tmp_size;
    x._capacity = tmp_capacity;
    _alloc.allocate(x._capacity);
    for(size_type i=0;i<x._size;i++)
    {
        _alloc.construct(&tmp[i], tmp[i]);
        _alloc.destroy(&tmp[i]);
    }
    _alloc.deallocate(tmp, tmp_capacity);
    tmp_capacity = 0;
    tmp_size = 0;
}
