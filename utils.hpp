#pragma once
#include <cstdint>
#include <typeinfo>


namespace ft
{

    template< bool B, class T = void >
    struct enable_if {};

    template<class T> //partial template specialisation
    struct enable_if<true, T> { typedef T type; };

    template< class T, T v >
    struct integral_constant
    {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
        operator T() { return v; }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template< class T >
    struct is_integral : false_type{};

    template <> struct is_integral<int> : true_type {};
    template <> struct is_integral<char> : true_type {};
    template <> struct is_integral<char16_t> : true_type {};
    template <> struct is_integral<char32_t> : true_type {};
    template <> struct is_integral<wchar_t> : true_type {};
    template <> struct is_integral<signed char> : true_type {};
    template <> struct is_integral<short int> : true_type {};
    template <> struct is_integral<bool> : true_type{};
    template <> struct is_integral<long int> : true_type {};
    template <> struct is_integral<long long int> : true_type {};
    template <> struct is_integral<unsigned char> : true_type {};
    template <> struct is_integral<unsigned short int> : true_type {};
    template <> struct is_integral<unsigned int> : true_type {};
    template <> struct is_integral<unsigned long int> : true_type {};
    template <> struct is_integral<unsigned long long int> : true_type {};

    template<class InputIt1, class InputIt2>
    bool equal( InputIt1 first1, InputIt1 last1,
                InputIt2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (*first1 != *first2)
            {
                return false;
            }
        }
        return true;
    }

    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare(	InputIt1 first1, InputIt1 last1,
                                     InputIt2 first2, InputIt2 last2 )
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    };
}

namespace ft
{
    // Iterator traits
    template <class Iterator>
    struct iterator_traits {
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::iterator_category iterator_category;
    };
    template <class T>
    struct iterator_traits<T*> {
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef T                               value_type;
        typedef ptrdiff_t                       difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };
    template <class T>
    struct iterator_traits<const T*> {
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef T                               value_type;
        typedef ptrdiff_t                       difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };

    // Iterator
    template <typename Category, typename T>
    struct iterator {
        typedef T*              pointer;
        typedef T&              reference;
        typedef T               value_type;
        typedef std::ptrdiff_t  difference_type;
        typedef Category        iterator_category;
    };
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };
    enum node_color{
        NODE_COLOR_BLACK,
        NODE_COLOR_RED,
    };

    template <typename T>
    struct is_pointer
    {
        static const bool value = false;
    };
    template <typename T>
    struct is_pointer<T *>
    {
        static const bool value = true;
    };
    template <typename T>
    struct is_void
    {
        static const bool value = false;
    };
    template <>
    struct is_void<void>
    {
        static const bool value = true;
    };

    template <class T>
    void swap (T & a, T & b)
    {
        T	tmp(a);
        a = b;
        b = tmp;
    }
}
