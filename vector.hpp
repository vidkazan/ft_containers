#pragma once
#include <memory>
#include "random_access_iterator.hpp"
#include "utils.hpp"
#include <stdexcept>

namespace ft
{
    template <typename T, typename Allocator = std::allocator<T> >
    class vector
    {
    public:
        typedef T														value_type;
        typedef Allocator												allocator_type;
        typedef typename allocator_type::reference						reference;
        typedef typename allocator_type::const_reference				const_reference;
        typedef typename allocator_type::pointer						pointer;
        typedef typename allocator_type::const_pointer					const_pointer;
        typedef	typename ft::random_access_iterator<value_type>			iterator;
        typedef	typename ft::const_random_access_iterator<value_type>	const_iterator;
        typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type		difference_type;
        typedef typename allocator_type::size_type						size_type;

        explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _capacity(0), _size(0) {
            _vector = _alloc.allocate(_capacity);
        };

        explicit vector(size_type count, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type())
                : _size(count), _alloc(alloc), _capacity(count) {
            _vector = _alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; i++) {
                _alloc.construct(&_vector[i], val);
            }
        };
        template <class InputIterator>
        vector (
                InputIterator first,
                InputIterator last,
                const allocator_type &alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0)
                 :
                _alloc(alloc),
                _size(0),
                _capacity(0)
        {
            this->assign(first, last);
        }
        vector( const vector& other ){};

//        Destructors

        ~vector(){
            this->clear();
            _alloc.deallocate(_vector, _capacity);
        };

        template <class InputIterator>
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
        assign(InputIterator first, InputIterator last)
        {
            int range_size;
            InputIterator tmp;
            tmp = first;
            range_size = 0;
            while (tmp != last)
            {
                tmp++;
                range_size++;
            }
            if (range_size < 0)
                throw std::length_error("Vector");
            this->clear();
            this->reserve(range_size);
            for (; first != last; ++first)
                this->push_back(*first);
        }

        void                    assign(size_type n, const value_type& val)
        {
            _size = n;
            _capacity = n;
            _alloc.allocate(_capacity);
            for(size_type i=0;i<_size;i++){
                _alloc.construct(&_vector[i], val);
            }
        };
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
        iterator begin (void)
        {
            return iterator(&_vector[0]);
        }
        const_iterator begin (void) const
        {
            return const_iterator(&_vector[0]);
        }
        iterator end (void)
        {
            return iterator(&_vector[0 + _size - 1]);
        }
        const_iterator end (void) const
        {
            return const_iterator(&_vector[0 + _size - 1]);
        }

        iterator erase(iterator position)
        {
            return (this->erase(position, position + 1));
        }
        iterator erase(iterator first, iterator last)
        {
            iterator	tmp;
            size_type	i;
            if (first == last)
                return (first);
            tmp = first;
            while (tmp != last)
            {
                _alloc.destroy(&(*tmp));
                tmp++;
                _size--;
            }
            tmp = first;
            i = 0;
            while (tmp != this->end())
            {
                _alloc.construct(&(*tmp), *(last + i));
                _alloc.destroy(&(*(last + i)));
                tmp++;
                i++;
            }
            return (first);
        }
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
        iterator insert(iterator position, const value_type &val)
        {
            iterator	it;
            size_type	index;
            index = position - this->begin();
            this->insert(position, 1, val);
            return iterator(this->begin() + index);
        }
        void insert(iterator position, size_type n, const value_type &val)
        {
            size_type	index;
            iterator	mv_dest;
            iterator	mv_source;
            size_type	new_capacity;
            if (n == 0)
                return ;
            index = position - this->begin();
            if (_size + n >= _capacity)
            {
                if (_size == 0)
                    new_capacity = 1;
                else
                    new_capacity = _size * 2;
                if (new_capacity < _size + n)
                    new_capacity = _size + n;
                this->reserve(new_capacity);
            }
            mv_source = this->end() - 1;
            mv_dest = mv_source + n;
            while (mv_source >= this->begin() + index)
            {
                _alloc.construct(&(*mv_dest), *mv_source);
                _alloc.destroy(&(*mv_source));
                mv_source--;
                mv_dest--;
            }
            mv_source++;
            for (size_type i = 0; i < n; i++)
            {
                _alloc.construct(&(*(mv_source)), val);
                mv_source++;
            }
            _size += n;
        }
        template <class InputIterator> typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
        insert(iterator position, InputIterator first, InputIterator last){}

//        reverse_iterator rbegin (void)
//        {
//            return reverse_iterator(this->end());
//        }
//        const_reverse_iterator rbegin(void) const
//        {
//            return const_reverse_iterator(this->end());
//        }
//        reverse_iterator rend(void)
//        {
//            return reverse_iterator(this->begin());
//        }
//        const_reverse_iterator rend(void) const
//        {
//            return const_reverse_iterator(this->begin());
//        }

        size_type               max_size() const{return _alloc.max_size();};
        vector&                 operator=(const vector& rhs)
        {
            this->clear();
            _alloc.deallocate(_vector, _capacity);

            _size = rhs.size();
            _capacity = rhs.capacity();
            _vector = _alloc.allocate(_capacity);
            for(size_type i=_size;i<_size;i++)
            {
                _alloc.construct(&_vector[i], rhs[i]);
            }
            return *this;
        };
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
            {
//                std::cout << "reserving " << _capacity * 1.5 <<"\n";
                reserve(((int)(_capacity * 1.5) + 1));
            }
            _alloc.construct(&_vector[_size],val);
            _size++;

        };
        void                    reserve (size_type n)
        {
            if(n <= _capacity)
                return;
            if(n > this->max_size())
                throw std::length_error("vector: resize: length > max_size");
            reallocateWithoutNewAssign(n);
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
            pointer tmp;
            size_type tmpSize;
            size_type tmpCap;

            tmpSize = x._size;
            tmpCap = x._capacity;
            tmp = x._vector;

            x._size = _size;
            x._capacity = _capacity;
            x._vector = _vector;
            _size = tmpSize;
            _capacity = tmpCap;
            _vector = tmp;
        };

    private:

        allocator_type			_alloc;
        size_type				_capacity;
        pointer					_vector;
        size_type               _size;

        void reallocateWithNewAssign(size_type n, value_type val)
        {
            size_type newCapacity = n;
            if(n < _capacity * 2) {
                newCapacity = _capacity*2;
            }
            pointer newVector = _alloc.allocate(newCapacity);
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
            _capacity = newCapacity;
        }
        void reallocateWithoutNewAssign(size_type n)
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

    template<class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        for (typename Alloc::size_type i = 0; i < lhs.size(); i++)
        {
            if (lhs[i] != rhs[i])
                return (false);
        }
        return (true);
    }

    template<class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (!(lhs == rhs));
    }


    template<class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template<class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (!(rhs < lhs));
    }

    template<class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (rhs < lhs);
    }

    template<class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (!(lhs < rhs));
    }

//    template<class T, class Alloc>
//    void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
//    {
//        x.swap(y);
//    }
    template <class T, class Alloc>
    void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
    {
        ft::vector<T, Alloc> tmp;
        tmp = x;
        x = y;
        y = tmp;
    }
};






