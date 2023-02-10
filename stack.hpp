#pragma once
# include "./vector.hpp"
namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef Container 							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

	protected:
		Container	c;

	public:
		explicit		stack(const Container & cont = Container());
						stack(const stack & copy);
					   ~stack();
		stack&			operator=(const stack &other);

		reference top();
		const_reference top() const;

		bool empty();
		size_type size();

		void push(const value_type &val);
		void pop() {c.pop_back();}

		friend bool operator==(const stack &lhs, const stack &rhs)				{ return lhs.c == rhs.c; };
		friend bool operator!=(const stack &lhs, const stack &rhs)				{ return lhs.c != rhs.c; };
		friend bool operator<=(const stack &lhs, const stack &rhs)				{ return lhs.c <= rhs.c; };
		friend bool operator>=(const stack &lhs, const stack &rhs)				{ return lhs.c >= rhs.c; };
		friend bool operator<(const stack &lhs, const stack &rhs)				{ return lhs.c < rhs.c; };
		friend bool operator>(const stack &lhs, const stack &rhs)				{ return lhs.c > rhs.c; };
	};

	template<class T, class Container>
	stack<T, Container>::stack(const Container &cont) : c(cont) {}

	template<class T, class Container>
	stack<T, Container>::stack(const stack &copy) : c(copy.c) {}

	template<class T, class Container>
	stack<T, Container>::~stack() {}

	template<class T, class Container>
	stack<T, Container>&
	stack<T, Container>::operator=(const stack &other) {c = other.c; return(*this);}

	template<class T, class Container>
	typename stack<T, Container>::reference
	stack<T, Container>::top() {return c.back();}

	template<class T, class Container>
	typename stack<T, Container>::const_reference
	stack<T, Container>::top() const {return c.back();}

	template<class T, class Container>
	bool
	stack<T, Container>::empty() {return c.empty();}

	template<class T, class Container>
	typename stack<T, Container>::size_type
	stack<T, Container>::size() {return c.size();}

	template<class T, class Container>
	void
	stack<T, Container>::push(const value_type &val) {c.push_back(val);}
}