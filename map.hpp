//
// Created by Dmitrii Grigorev on 29.04.22.
//
#include <iomanip>
#define RED "\e[0;31m"
#define BLUE "\e[0;36m"
#define LIGHT_GREY "\e[0;37m"
#define GREY "\e[0;90m"
#define WHITE "\e[0;38m"
#define WHITE_LINE "\e[4;37m"
#define RED_LINE "\e[4;31m"
#include <iostream>
using namespace std;
namespace ftm {

    enum node_color{
        NODE_COLOR_RED,
        NODE_COLOR_BLACK,
    };
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
        typedef ft::random_access_iterator_tag iterator_category;
    };
    template <class T>
    struct iterator_traits<const T*> {
        typedef const T*                       pointer;
        typedef const T&                       reference;
        typedef T                              value_type;
        typedef ptrdiff_t                      difference_type;
        typedef ft::random_access_iterator_tag iterator_category;
    };
    template <class T>
    struct node{
        typedef node<T> node_type;

        node_color color;
        T data;
        node_type * left;
        node_type * right;
        node_type * parent;
    public:
        node(T data)
                : data(data)
                , color(NODE_COLOR_RED)
                , left(NULL)
                , right(NULL)
                , parent(NULL) {};
    };
    template <typename T>
    struct map_iterator {

    public:
        typedef node<T>	 node_type;
        typedef node<T> * node_pointer;

        typedef iterator_traits<T *>					_traits_type;
        typedef typename _traits_type::pointer 		    pointer;
        typedef typename _traits_type::value_type      	value_type;
        typedef typename _traits_type::reference      	reference;
        typedef typename _traits_type::difference_type 	difference_type;
        typedef bidirectional_iterator_tag 				iterator_category;

    private:
        node_pointer _current;

    public:
        map_iterator(void) : _current(NULL) { }

        explicit
        map_iterator(node_pointer node) : _current(node) { }

        map_iterator(const map_iterator<T> &it) : _current(it.base()) {}

        node_pointer
        base(void) const {
            return _current;
        }

        reference
        operator*(void) const {
            return _current->data;
        }

        pointer
        operator->(void) const {
            return &(_current->data);
        }

        map_iterator
        operator++(void) {
            _current = increment(_current);
            return *this;
        }

        map_iterator
        operator--(void) {
            _current = decrement(_current);
            return *this;
        }

        map_iterator
        operator++(int) {
            map_iterator tmp = *this;
            _current = increment(_current);

            return tmp;
        }

        map_iterator
        operator--(int) {
            map_iterator tmp = *this;
            _current = decrement(_current);

            return tmp;
        }

        inline bool
        operator==(const map_iterator<T> &rhs) const
        { return base() == rhs.base(); }

        inline bool
        operator!=(const map_iterator<T> &rhs) const
        { return base() != rhs.base(); }
    };

    template <typename T>
    struct map_const_iterator {

    public:
        typedef map_iterator<T>		non_const_iterator;
        typedef node<T>			node_type;
        typedef node<T> * 		node_pointer;

        typedef iterator_traits<const T *>				_traits_type;
        typedef typename _traits_type::pointer 		    pointer;
        typedef typename _traits_type::value_type      	value_type;
        typedef typename _traits_type::reference      	reference;
        typedef typename _traits_type::difference_type 	difference_type;

        typedef bidirectional_iterator_tag 				iterator_category;

    private:
        node_pointer _current;

    public:
        map_const_iterator(void) : _current(NULL) { }

        explicit
        map_const_iterator(node_pointer node) : _current(node) { }

        map_const_iterator(const non_const_iterator &it) : _current(it.base()) { }

        map_const_iterator(const map_const_iterator &it) : _current(it.base()) {}

        node_pointer
        base(void) const {
            return _current;
        }

        reference
        operator*(void) const {
            return _current->data;
        }

        pointer
        operator->(void) const {
            return &(_current->data);
        }

        map_const_iterator
        operator++(void) {
            _current = increment(_current);
            return *this;
        }

        map_const_iterator
        operator--(void) {
            _current = decrement(_current);
            return *this;
        }

        map_const_iterator
        operator++(int) {
            map_const_iterator tmp = *this;
            _current = increment(_current);

            return tmp;
        }

        map_const_iterator
        operator--(int) {
            map_const_iterator tmp = *this;
            _current = decrement(_current);

            return tmp;
        }

        inline bool
        operator==(const map_const_iterator<T> &rhs) const
        { return base() == rhs.base(); }

        inline bool
        operator!=(const map_const_iterator<T> &rhs) const
        { return base() != rhs.base(); }
    };

    template<class T, class Compare = std::less<T>,
            class Allocator = allocator<T> >
    class map {
    public:
        // types
        typedef             node<T>                                         node_type;
        typedef             T                                               value_type;
        typedef             Compare                                         key_compare;
        typedef             Allocator                                       allocator_type;
        typedef typename    allocator_traits<Allocator>::pointer            pointer;
        typedef typename    allocator_traits<Allocator>::const_pointer      const_pointer;
        typedef             value_type&                                     reference;
        typedef const       value_type&                                     const_reference;
        typedef             size_t                                          size_type;
        typedef             ptrdiff_t                                       difference_type;

        typedef             map_iterator<value_type>                        iterator;
        typedef             map_const_iterator<value_type>                  const_iterator;

        typedef             reverse_iterator<const_iterator>                const_reverse_iterator;
        typedef             reverse_iterator<iterator>                      reverse_iterator;


        // construct/copy/destroy
                        map(){ }
        explicit        map(const Compare& comp, const Allocator& = Allocator()){};

        template<class InputIt>
                        map(InputIt first, InputIt last,
                            const Compare& comp = Compare(), const Allocator& = Allocator()){};
                        map(const map& x){};
                        ~map(){};

        map&            operator=(const map& x);
        allocator_type  get_allocator() const;

        const_iterator root(void) const;


        // iterators
//        iterator               begin();
//        iterator               end();
//        reverse_iterator       rbegin();
//        reverse_iterator       rend();

        const_iterator         begin() const{return const_iterator(_root);};
        const_iterator         end() const;
//        const_reverse_iterator rbegin() const;
//        const_reverse_iterator rend() const;

        // capacity
        bool                                        empty() const{return true;};
        size_type                                   size() const{};
        size_type                                   max_size() const{};

        // modifiers
        pair<iterator, bool>                        insert(const value_type& x){return std::make_pair(map_iterator<int>(_root),true);};
        iterator                                    insert(const_iterator position, const value_type& x){};
        template<class InputIt>
        void                                        insert(InputIt first, InputIt last){};

        iterator                                    erase(iterator position){return nullptr;};
        iterator                                    erase(const_iterator position){return nullptr;};
        size_type                                   erase(const_reference x){return 0;};
        iterator                                    erase(const_iterator first, const_iterator last){return nullptr;};

        void                                        swap(map&){};

        void                                        clear(){};

        // observers
        key_compare                                 key_comp() const{};

        // map operations
//        iterator                                    find(const key_type& x);
//        const_iterator                              find(const key_type& x) const;

//        size_type                                   count(const_reference x) const;

//        iterator                                    lower_bound(const key_type& x);
//        const_iterator                              lower_bound(const key_type& x) const;

//        iterator                                    upper_bound(const key_type& x);
//        const_iterator                              upper_bound(const key_type& x) const;

//        pair<iterator, iterator>                    equal_range(const key_type& x);
//        pair<const_iterator, const_iterator>        equal_range(const key_type& x) const;
    private:
        node_type *			_root;
        size_type			_size;
    };

    template <typename T, typename Compare, typename Alloc >
    typename map<T, Compare, Alloc>::const_iterator
    map<T, Compare, Alloc>::root(void) const {
        return const_iterator(_root);
    }
    // swap
//    template<class Key, class T, class Compare, class Allocator>
//    void swap(map<T, Compare, Allocator>& x,
//              map<T, Compare, Allocator>& y);
}
//
//namespace ftm{
//    typedef struct      s_node node;
//    struct s_node{
//            node*   parent;
//            node*   left;
//            node*   right;
//            int     key;
//            int     val;
//            bool    color; //  0 black / 1 red
//    };
//    class map{
//        public:
//            map(): _root(nullptr), _debug(0){};
//            map(int key, int val) : _debug(0) {}
//            ~map(){};
//            void    append(int key,int val){};
//            void    print(int level, node *ptr)
//            {
//                int i;
//                if (ptr != NULL)
//                {
//                    print(level + 1, ptr->right);
//                    cout << "\n";
//                    for (i = 0; i < level && ptr != _root; i++)
//                        cout << "     ";
//                    if(ptr->color)
//                        printNodeAdr(ptr,1);
//                    else
//                        printNodeAdr(ptr,0);
//                    print(level + 1, ptr->left);
//                }
//            }
//            void    printNodeAdr(node* ptr, bool color){
//                if(_debug)
//                {
//                    cout << BLUE;
//                    if (ptr->parent)
//                        cout << to_string((long) ptr->parent).substr(13, 2);
//                    else
//                        cout << "00";
//                }
//                cout << GREY;
//
//                if(color)
//                    cout << RED_LINE << ptr->key << GREY;
//                else
//                    cout << WHITE_LINE << ptr->key << GREY;
//                if(_debug) {
//                    cout << BLUE << to_string((long) ptr).substr(13, 2) << GREY;
//
//                    if (ptr->left)
//                        cout << to_string((long) ptr->left).substr(13, 2);
//                    else
//                        cout << "00";
//
//                    if (ptr->right)
//                        cout << to_string((long) ptr->right).substr(13, 2);
//                    else
//                        cout << "00";
//                }
//                cout << WHITE;
//            }
//            void    setDebugMode() {_debug = 1;};
//            node*   getRoot(){return _root;}
//            void    erase(int key){}
//            size_t  size(){
//                return 0;
//            }
//            bool    empty(){
//                return true;
//            }
//            node* base(node * node){
//                return NULL;
//            }
//        private:
//            node*   _root;
//            bool _debug;
//
//    };
//}