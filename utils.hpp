#pragma once
#include <stdint.h>
namespace ft
    {

        template< bool B, class T = void >
        struct enable_if {};
        template<class T>
        struct enable_if<true, T> { typedef T type; };

//        template< class T, T v >
//        struct integral_constant
//        {
//            static const T value = v;
//            typedef T value_type;
//            typedef integral_constant<T, v> type;
//            operator T() { return v; }
//        };
//
//        typedef integral_constant<bool, true> true_type;
//        typedef integral_constant<bool, false> false_type;

        template< class T >
        struct is_integral : std::false_type{};

        template <> struct is_integral<int>                     : std::true_type {};
        template <> struct is_integral<char>                    : std::true_type {};
        template <> struct is_integral<char16_t>                : std::true_type {};
        template <> struct is_integral<char32_t>                : std::true_type {};
        template <> struct is_integral<wchar_t>                 : std::true_type {};
        template <> struct is_integral<signed char>             : std::true_type {};
        template <> struct is_integral<short int>               : std::true_type {};
        template <> struct is_integral<bool>                    : std::true_type{};
        template <> struct is_integral<long int>                : std::true_type {};
        template <> struct is_integral<long long int>           : std::true_type {};
        template <> struct is_integral<unsigned char>           : std::true_type {};
        template <> struct is_integral<unsigned short int>      : std::true_type {};
        template <> struct is_integral<unsigned int>            : std::true_type {};
        template <> struct is_integral<unsigned long int>       : std::true_type {};
        template <> struct is_integral<unsigned long long int>  : std::true_type {};

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

        template< typename T1, typename T2 >
        struct pair
        {
            T1	first;
            T2	second;

            pair(void) : first(), second() {};
            template<class U, class V>
            pair (const pair<U,V> &pr) : first(pr.first), second(pr.second) {}
            pair(const T1 &x, const T2 &y) : first(x), second(y) {};
            pair &operator=( const pair &other )
            {
                first = other.first;
                second = other.second;
                return (*this);
            }

        };

        template< class T1, class T2 >
        bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        {
            if (lhs.first == rhs.first && lhs.second == rhs.second)
                return (true);
            return (false);
        }

        template< class T1, class T2>
        bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {return(!(lhs==rhs));}

        template< class T1, class T2>
        bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            if (lhs.first<rhs.first)
                return (true);
            if (rhs.first<lhs.first)
                return (false);
            if (lhs.second<rhs.second)
                return (true);
            return (false);
        }

        template< class T1, class T2>
        bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {return(!(rhs < lhs));}

        template< class T1, class T2>
        bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {return(rhs < lhs);}

        template< class T1, class T2>
        bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {return (!(lhs < rhs));}

        template< class T1, class T2 >
        pair<T1,T2> make_pair( T1 x, T2 y )
        {
            return pair<T1,T2>(x ,y);
        }
    }

namespace ftm
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
        typedef T*                             pointer;
        typedef T&                             reference;
        typedef T                              value_type;
        typedef ptrdiff_t                      difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };
    template <class T>
    struct iterator_traits<const T*> {
        typedef const T*                       pointer;
        typedef const T&                       reference;
        typedef T                              value_type;
        typedef ptrdiff_t                      difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };

    // Iterator
    template <typename Category, typename T, typename Distance = std::ptrdiff_t, typename Pointer = T*, typename Reference = T&>
    struct iterator {
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Category  iterator_category;
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
    template<bool B, class T = void>
    struct enable_if
    {};

    template<class T>
    struct enable_if<true, T>
    { typedef T type; };

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    };

    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1 != last1)
        {
            if (*first1 != *first2)
                return false;
            ++first1;
            ++first2;
        }
        return true;
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
    template <typename T>
    struct is_integral
    {
        static const bool value = false;
    };
    template <>
    struct is_integral<bool>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<char>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned char>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<long>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<long unsigned>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<short>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<short unsigned>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<long long>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<long long unsigned>
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
