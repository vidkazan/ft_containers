#pragma once
# include <iterator>
namespace ft {
    template<class T, class Category = std::random_access_iterator_tag, class Distance = ptrdiff_t,
            class Pointer = T *, class Reference = T &>
    class VectorIterator {
    public:
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    protected:
        pointer _ptr;
    public:
        VectorIterator(void) {
            /* NOP */
        }

        VectorIterator(const VectorIterator &other) {
            _ptr = other.get_internal_pointer();
        }

        VectorIterator(pointer ptr)
                : _ptr(ptr) {
            /* NOP */
        }

        ~VectorIterator(void) {
            /* NOP */
        }

        pointer get_internal_pointer(void) const {
            return _ptr;
        }

        operator VectorIterator<const T>(void) const {
            return VectorIterator<const T>(this->_ptr);
        }

        VectorIterator &operator=(const VectorIterator<const T> &other) {
            if (this != &other)
                _ptr = other.get_internal_pointer();
            return *this;
        }

        VectorIterator &operator++(void) {
            _ptr++;
            return *this;
        }

        VectorIterator &operator--(void) {
            _ptr--;
            return *this;
        }

        VectorIterator operator++(int) {
            VectorIterator tmp(*this);
            operator++();
            return tmp;
        }

        VectorIterator operator--(int) {
            VectorIterator tmp(*this);
            operator--();
            return tmp;
        }

        bool operator==(const VectorIterator<const T> &other) const {
            return (_ptr == other.get_internal_pointer());
        }

        bool operator!=(const VectorIterator<const T> &other) const {
            return (_ptr != other.get_internal_pointer());
        }

        bool operator>(const VectorIterator<const T> &other) const {
            return (_ptr > other.get_internal_pointer());
        }

        bool operator>=(const VectorIterator<const T> &other) const {
            return (_ptr >= other.get_internal_pointer());
        }

        bool operator<(const VectorIterator<const T> &other) const {
            return (_ptr < other.get_internal_pointer());
        }

        bool operator<=(const VectorIterator<const T> &other) const {
            return (_ptr <= other.get_internal_pointer());
        }

        value_type &operator*(void) {
            return (*_ptr);
        }

        value_type *operator->(void) {
            return (_ptr);
        }

        VectorIterator operator+(int n) const {
            VectorIterator tmp(*this);
            tmp += n;
            return (tmp);
        }

        VectorIterator operator-(int n) const {
            VectorIterator tmp(*this);
            tmp -= n;
            return (tmp);
        }

        friend VectorIterator operator+(std::ptrdiff_t n, VectorIterator it) {
            VectorIterator tmp(it.get_internal_pointer());
            tmp += n;
            return (tmp);
        }

        int operator-(VectorIterator<const T> const &other) const {
            return _ptr - other.get_internal_pointer();
        }

        VectorIterator &operator+=(int n) {
            _ptr += n;
            return *this;
        }

        VectorIterator &operator-=(int n) {
            _ptr -= n;
            return *this;
        }

        value_type &operator[](int n) const {
            return _ptr[n];
        }
    };
}