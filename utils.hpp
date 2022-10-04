#pragma once

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
}
