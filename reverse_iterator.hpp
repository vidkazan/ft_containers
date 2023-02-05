#pragma once
#include "random_access_iterator.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator : public iterator<	typename iterator_traits<Iterator>::iterator_category,
												typename iterator_traits<Iterator>::value_type>
	{
	private: //deprecated
		Iterator _it;

	public:
		Iterator current;

	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef typename iterator_traits<Iterator>::pointer				pointer;

		reverse_iterator(void) : _it(), current() {}
		explicit reverse_iterator(iterator_type _x) : _it(_x), current(_x) {}
		template<typename U>
		reverse_iterator(const reverse_iterator<U> &copy) : _it(copy.base()), current(copy.base()) {}
		template<typename U>
		reverse_iterator	&operator=(const reverse_iterator<U> &other) {_it = current = other.base(); return (*this);}

		iterator_type		base(void)						const	{return(current);}
		reference			operator*(void)					const	{iterator_type tmp = current; return *--tmp;}
		pointer				operator->(void)				const	{return (&(operator*()));}
		reverse_iterator	&operator++(void)						{current--; return(*this);}
		reverse_iterator	operator++(int)							{reverse_iterator temp = *this; current--; return (temp);}
		reverse_iterator	&operator--(void)						{current++; return(*this);}
		reverse_iterator	operator--(int)							{reverse_iterator temp = *this; current++; return (temp);}
		reverse_iterator	operator+(difference_type n)	const	{return (reverse_iterator(current - n));}
		reverse_iterator	&operator+=(difference_type n)			{current -= n; return (*this);}
		reverse_iterator	operator-(difference_type n)	const	{return (reverse_iterator(current + n));}
		reverse_iterator	&operator-=(difference_type n)			{current += n; return (*this);}
		reference			operator[](difference_type n)	const	{return (*(*this + n));}
	};

	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return (lhs.base() == rhs.base());}

	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return (lhs.base() > rhs.base());}

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return (lhs.base() != rhs.base());}

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return (lhs.base() < rhs.base());}

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return (lhs.base() <= rhs.base());}

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
		{return (lhs.base() >= rhs.base());}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y)
		{return (y.base() - x.base());}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x)
		{return (reverse_iterator<Iterator>(x.base() - n));}
}