#pragma once
#include <memory>
#include "random_access_iterator.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <iostream>

namespace ft {
    template<typename T, typename Alloc = std::allocator<T> >
    class vector {
    public:
        typedef 			T 												value_type;
        typedef 			Alloc 											allocator_type;
        typedef typename 	allocator_type::reference						reference;
        typedef typename 	allocator_type::const_reference					const_reference;
        typedef typename 	allocator_type::pointer 						pointer;
        typedef typename 	allocator_type::const_pointer 					const_pointer;
        typedef typename 	ft::random_access_iterator<value_type> 			iterator;
        typedef typename 	ft::const_random_access_iterator<value_type> 	const_iterator;
        typedef typename 	ft::reverse_iterator<iterator>					reverse_iterator;
        typedef typename 	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
        typedef typename 	iterator_traits<iterator>::difference_type		difference_type;
        typedef typename 	allocator_type::size_type size_type;

        explicit vector(const allocator_type &alloc = allocator_type());
        explicit vector(
                size_type count,
                const value_type &val = value_type(),
                const allocator_type &alloc = allocator_type());

        template<class InputIterator>
        vector(
                InputIterator first,
                InputIterator last,
                const allocator_type &alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type * = 0);

        vector(const vector &other);
        ~vector();

        template<class InputIterator>
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
                        assign(InputIterator first, InputIterator last);
        void            assign(size_type n, const value_type &val);
        reference       at(size_type n);
        const_reference at(size_type n) const;
        reference       front();
        const_reference front() const;
        reference       back();
        const_reference back() const;
        iterator        begin(void);
        const_iterator  begin(void) const;
        iterator        end(void);
        const_iterator  end(void) const;
        reverse_iterator        rbegin(void);
        const_reverse_iterator  rbegin(void) const;
        reverse_iterator        rend(void);
        const_reverse_iterator  rend(void) const;
        iterator        erase(iterator position);
        iterator        erase(iterator first, iterator last);
        size_type       capacity() const;
        void            clear();
        bool            empty() const;
        allocator_type  get_allocator() const;
        iterator        insert(iterator position, const value_type &val);
        void            insert(iterator position, size_type n, const value_type &val);
		template<class InputIterator>
		void 			insert(iterator position,InputIterator first,InputIterator last,typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0);
        size_type       max_size() const;
        vector&         operator=(const vector &rhs);
        reference       operator[](size_type n);
        const_reference operator[](size_type n) const;
        void            pop_back();
        void            push_back(const value_type &val);
        void            reserve(size_type n);
        void            resize(size_type n, value_type val = value_type());
        size_type       size() const;
        void            swap(vector &x);
		value_type*			data(void);
		const value_type*	data(void) const;
    private:

        allocator_type	_alloc;
        size_type		_capacity;
        pointer 		_vector;
        size_type		_size;

        void            reallocateWithNewAssign(size_type n, value_type val);
        void            reallocateWithoutNewAssign(size_type n);
    };

    template<class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        if (lhs.size() != rhs.size())
            return (false);
        for (typename Alloc::size_type i = 0; i < lhs.size(); i++) {
            if (lhs[i] != rhs[i])
                return (false);
        }
        return (true);
    }

    template<class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return (!(lhs == rhs));
    }

    template<class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template<class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return (!(rhs < lhs));
    }

    template<class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return (rhs < lhs);
    }

    template<class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return (!(lhs < rhs));
    }

    template<class T, class Alloc>
    vector<T, Alloc>::vector(const allocator_type &alloc)
        :_alloc(alloc),_capacity(0),_size(0)

    {
        _vector = _alloc.allocate(_capacity);
    }

    template<class T, class Alloc>
    vector<T, Alloc>::vector(size_type count, const value_type &val,const allocator_type &alloc)
        :
        _alloc(alloc),_capacity(count),_size(count)
    {
        _vector = _alloc.allocate(_capacity);
        for (size_type i = 0; i < _size; i++) {
            _alloc.construct(&_vector[i], val);
        }
    }

    template<class T, class Alloc>
    template <class InputIterator>
    vector<T, Alloc>::vector (
                InputIterator first,
                InputIterator last,
                const allocator_type &alloc,
                typename enable_if<!is_integral<InputIterator>::value, void>::type*)
        :
        _alloc(alloc),_capacity(0),_size(0)

    {
        _vector = _alloc.allocate(_capacity);
        this->assign(first, last);
    }

    template<class T, class Alloc>
    vector<T, Alloc>::vector ( const vector& other )
    {
        _vector = _alloc.allocate(other.capacity());
        _capacity = other.size();
        _size = other.size();
        for (size_type i = 0; i < _size; i++) {
            _alloc.construct(&_vector[i], other[i]);
        }
    }

    template<class T, class Alloc>
    vector<T, Alloc>::~vector()
    {
//		std::cout
//			<< "\n====================================================\n"
//			<< "obj " << this << "\n"
//			<< "alloc " << &_alloc << "\n"
//			<< "vector: " << _vector << "\n"
//				<< "vector[0]: " << &_vector[0] << "\n"
//			<< "Clearing...\n";
        this->clear();
        _alloc.deallocate(_vector, _capacity);
    }

    template<class T, class Alloc>
    template <class InputIterator>
    typename enable_if<!is_integral<InputIterator>::value, void>::type
    vector<T, Alloc>::assign(InputIterator first, InputIterator last)
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
            throw std::length_error("vector::assign range_size < 0");
        this->clear();
        this->reserve(range_size);
        for (; first != last; ++first)
            this->push_back(*first);
    }

    template<class T, class Alloc>
    void
    vector<T, Alloc>::assign(size_type n, const value_type& val)
    {
        _size = n;
        _capacity = _capacity > n ? _capacity : n;
		_alloc.deallocate(_vector,_capacity);
        _vector = _alloc.allocate(_capacity);
        for(size_type i=0;i<_size;i++) {
            _alloc.construct(&_vector[i], val);
        }
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::reference
    vector<T, Alloc>::at(size_type n)
    {
        if(n < _size)
            return _vector[n];
        throw std::out_of_range("ft::vector.at() out of range");
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_reference
    vector<T, Alloc>::at(size_type n) const
    {
        if(n <= _size - 1)
            return _vector[n];
        throw std::out_of_range("ft::vector.at() out of range");
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::reference    vector<T, Alloc>::front()
    {
		return _vector[0];
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_reference    vector<T, Alloc>::front() const
    {
		return _vector[0];
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::reference    vector<T, Alloc>::vector<T, Alloc>::back()
    {
		return _size ? _vector[_size-1] : _vector[0];
    }

    template<class T, class Alloc>
    typename vector<T, Alloc>::const_reference    vector<T, Alloc>::back() const
    {
		return _size ? _vector[_size-1] : _vector[0];
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::begin(void)
    {
        return(iterator(_vector));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin(void) const
    {
        return(const_iterator(_vector));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::end(void)
    {
        return(iterator(_vector + _size));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end(void) const
    {
        return(const_iterator(_vector + _size));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin(void)
    {
        return(static_cast<reverse_iterator>(end()));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin(void) const
    {
        return(static_cast<const_reverse_iterator>(end()));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend(void)
    {
        return(static_cast<reverse_iterator>(begin()));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend(void) const
    {
        return(static_cast<const_reverse_iterator>(begin()));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::erase(iterator position)
    {
        return (this->erase(position, position + 1));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::erase(iterator first, iterator last)
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

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::size_type
    vector<T, Alloc>::capacity() const{return _capacity;}


	template <typename T, typename Allocator>
	void vector<T, Allocator>::clear(void)
	{
		size_type old_size = size();
		vector<T,Allocator>::pointer p = this->end().base();

		for(size_type i = 0; i < old_size; i++)
		{
			p--;
			_size--;
			_alloc.destroy(p);
		}
		_size = 0;
	}

    template<typename T, typename Alloc>
    bool
    vector<T, Alloc>::empty() const{return _size == 0;}

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::allocator_type
    vector<T, Alloc>::get_allocator() const{return _alloc;}

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::insert(iterator position, const value_type &val)
    {
        iterator	it;
        size_type	index;
        index = position - this->begin();
        this->insert(position, 1, val);
        return iterator(this->begin() + index);
    }

    template<typename T, typename Alloc>
    void
    vector<T, Alloc>::insert(iterator position, size_type n, const value_type &val)
    {
        size_type	index;
        iterator	mv_dest;
        iterator	mv_source;
        size_type	new_capacity;
        if (n == 0)
            return ;
        index = position - this->begin();
        if (_size + n > _capacity)
        {
            if (_size == 0) {
                new_capacity = 1;
            } else {
                new_capacity = _capacity * 2;
            }
            if (new_capacity < _size + n) {
                new_capacity = _size + n;
            }
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
    //            std::cout << "/\n";
    }

    template<typename T, typename Alloc>
    template <class InputIterator>
    void	vector<T, Alloc>::insert (iterator position, InputIterator first, InputIterator last,typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type*)
    {

        size_type n = last - first;
//        std::cout << "          insert range: ";
        if ((_capacity - _size) >= n)
        {
            std::cout << "without relocate\n";
            for (size_type i = 0; i < (size() - (&(*position) - _vector)); i++)
                _alloc.construct(this->end().base() - i + n - 1, *(this->end() - i - 1));
            while (first != last)
            {
                _alloc.construct(&(*position), *first);
                first++;
                position++;
            }
            _size +=n;
        }
        else
        {
//            std::cout << "with! relocate\n";
            size_type n_cap = 1;
            if (_capacity)
                n_cap = _capacity * 2;
            if (n + size() > 2 * _capacity)
                n_cap = n + size();

            pointer new_start = _alloc.allocate(n_cap);
            pointer new_end = new_start;
            try
            {
                for (int i = 0; i < &(*position) - _vector; i++)
                {
                    _alloc.construct(new_start + i, *(_vector + i));
                    new_end++;
                }
                for (int j = 0; first != last; first++, j++)
                {
                    _alloc.construct(new_start + (&(*position) - _vector) + j, *first);
                    new_end++;
                }
                for (size_type k = 0; k < size() - (&(*position) - _vector); k++)
                {
                    _alloc.construct(new_start + (&(*position) - _vector) + n + k, *(&(*position) + k));
                    new_end++;
                }
            }
            catch (...)
            {
                while (new_start != new_end)
                    _alloc.destroy(new_end--);
                _alloc.destroy(new_end);
                _alloc.deallocate(new_start, n_cap);
                throw ;
            }
            for (size_type l = 0; l < size(); l++)
            {
                _alloc.destroy(_vector + l);
            }
            _alloc.deallocate(_vector, _capacity);
            _vector = new_start;
            _capacity = n_cap;
            _size = new_end - new_start;
        }
    }


    template<typename T, typename Alloc>
    typename vector<T, Alloc>::size_type
    vector<T, Alloc>::max_size() const{return _alloc.max_size();}

    template<typename T, typename Alloc>
    vector<T, Alloc> &
    vector<T, Alloc>::operator=(const vector& rhs)
    {
        this->clear();
        _alloc.deallocate(_vector, _capacity);

        _size = rhs.size();
        _capacity = rhs.size();
        _vector = _alloc.allocate(_capacity);
        for (size_type i = 0; i < _size; i++) {
            _alloc.construct(&_vector[i], rhs[i]);
        }
		return *this;
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reference
    vector<T, Alloc>::operator[](size_type n){return _vector[n];}

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reference
    vector<T, Alloc>::operator[](size_type n) const{return _vector[n];}

    template<typename T, typename Alloc>
    void
    vector<T, Alloc>::pop_back()
    {
        if(_size == 0)
            return;
        _alloc.destroy(&_vector[_size - 1]);
        _size-=1;
    }

    template<typename T, typename Alloc>
    void
    vector<T, Alloc>::push_back(const value_type& val)
    {
        if((_size + 1) > _capacity)
        {
            _capacity ? reserve(((int)(_capacity) * 2)) : reserve((1));
        }
        _alloc.construct(&_vector[_size],val);
        _size++;

    }

    template<typename T, typename Alloc>
    void
    vector<T, Alloc>::reserve (size_type n)
    {
        if(n <= _capacity)
            return;
        if(n > this->max_size())
            throw std::length_error("vector: resize: length > max_size");
        reallocateWithoutNewAssign(n);
    }

    template<typename T, typename Alloc>
    void
    vector<T, Alloc>::resize (size_type n, value_type val)
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
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::size_type
    vector<T, Alloc>::size() const{return _size;}

    template<typename T, typename Alloc>
    void
    vector<T, Alloc>::swap (vector& x)
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
    }

    template<typename T, typename Alloc>
    void
    vector<T, Alloc>::reallocateWithNewAssign(size_type n, value_type val)
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
        if(_capacity)
            _alloc.deallocate(_vector, _capacity);
        for(size_type i=_size;i<n;i++)
        {
            _alloc.construct(&newVector[i], val);
        }
        _vector = newVector;
        _size = n;
        _capacity = newCapacity;
    }

    template<typename T, typename Alloc>
    void
    vector<T, Alloc>::reallocateWithoutNewAssign(size_type n)
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
	template <typename T, typename Allocator>
	typename vector<T, Allocator>::value_type* vector<T, Allocator>::data()
	{return (_vector);}

	template <typename T, typename Allocator>
	const typename vector<T, Allocator>::value_type* vector<T, Allocator>::data() const
	{return (_vector);}
}





