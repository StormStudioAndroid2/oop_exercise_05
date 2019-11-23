
#ifndef D_LIST_H_
#define D_LIST_H_

#include <iostream>
#include <memory>
#include <functional>
#include <cassert>
#include <iterator>


namespace containers {

    template<class T>
    struct list {
    private:
        struct node;

    public:
        list() = default;
        T End();
        T& operator[] (const int index);
        size_t Size();
        struct forward_iterator {
            using value_type = T;
            using reference = T &;
            using pointer = T *;
            using difference_type = ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            forward_iterator(node *ptr);

            T &operator*();

            forward_iterator &operator++();

            forward_iterator operator+(int r);

            bool operator==(const forward_iterator &o) const;

            bool operator!=(const forward_iterator &o) const;

        private:
            node *ptr_;

            friend list;

        };

        forward_iterator begin();

        forward_iterator end();

        void insert(const forward_iterator &it, const T &value);

        void erase(const forward_iterator &it);

        void popStart();
        void popEnd();

        void add(const T &value);

        T front();
        
    private:
        node *end_node = nullptr;

        node *getTail(node *ptr);

        struct node {
            T value;
            std::unique_ptr<node> next = nullptr;
            node *parent = nullptr;

            forward_iterator nextf();
        };

        std::unique_ptr<node> root = nullptr;
        node* rootEnd = nullptr;

    };


//
template<class T>
size_t list<T>::Size() {
    auto it = begin();
    size_t size1 = 0;
    while(it!=0) {
        ++it;
        size1++;
    }
    return size1;
}
    template<class T>
    typename list<T>::node *list<T>::getTail(containers::list<T>::node *ptr) {
        if ((ptr == nullptr) || (ptr->next == nullptr)) {
            return ptr;
        }
        return list<T>::getTail(ptr->next.get());
    }


    template<class T>
    typename list<T>::forward_iterator list<T>::begin() {
        if (root == nullptr) {
            return nullptr;
        }
        forward_iterator it(root.get());
        return it;
    }

    template<class T>
    typename list<T>::forward_iterator list<T>::end() {
        return nullptr;
    }

    template<class T>
    void list<T>::insert(const list<T>::forward_iterator &it, const T &value) {
        std::unique_ptr<node> new_node(new node{value});
        if (it != nullptr) {
            node *ptr = it.ptr_->parent;
            new_node->parent = it.ptr_->parent;
            it.ptr_->parent = new_node.get();
            if (ptr) {
                new_node->next = std::move(ptr->next);
                ptr->next = std::move(new_node);
            } else {
                new_node->next = std::move(root);
                root = std::move(new_node);
            }
        } else {
            new_node->next = nullptr;
            if(end_node==nullptr) {
                new_node->parent= nullptr;
                new_node->next= nullptr;
                list<T>::root = std::move(new_node);
            }else{
                new_node->parent=end_node;
                new_node->next= nullptr;
                end_node->next=std::move(new_node);
            }
        }
        
        end_node = getTail(root.get());
    }
    template<class T>
    T list<T>::End() {
        return end_node->value;
    }
    template<class T>
    void list<T>::erase(const list<T>::forward_iterator &it) {
        if (it.ptr_ == nullptr) {
            throw std::logic_error("erasing invalid iterator");
        }
        std::unique_ptr<node> &pointer_from_parent = [&]() -> std::unique_ptr<node> & {
            if (it.ptr_ == root.get()) {
                return root;
            }
            return it.ptr_->parent->next;
        }();
        pointer_from_parent = std::move(it.ptr_->next);

        end_node = getTail(root.get());
    }

//
    template<class T>
    typename list<T>::forward_iterator list<T>::node::nextf() {
        forward_iterator result(this->next.get());
        return result;
    }
template<class T>
T&  list<T>::operator[] (const int index) {
    if (index>Size()) {
            throw std::logic_error("invalid index");

    }
    auto it = this->begin()+index;
    return *it;
}
 
    template<class T>
    list<T>::forward_iterator::forward_iterator(node *ptr): ptr_{ptr} {}

    template<class T>
    T &list<T>::forward_iterator::operator*() {
        return ptr_->value;
    }

    template<class T>
    typename list<T>::forward_iterator &list<T>::forward_iterator::operator++() {
        if (*this != nullptr) {
            *this = ptr_->nextf();
            return *this;
        } else {
            throw std::logic_error("invalid iterator");
        }
    }

    template<class T>
    typename list<T>::forward_iterator list<T>::forward_iterator::operator+(int r) {
        for (int i = 0; i < r; ++i) {
            ++*this;
        }
        return *this;
    }

    template<class T>
    bool list<T>::forward_iterator::operator==(const forward_iterator &o) const {
        return ptr_ == o.ptr_;
    }

    template<class T>
    bool list<T>::forward_iterator::operator!=(const forward_iterator &o) const {
        return ptr_ != o.ptr_;
    }

    template<class T>
    T list<T>::front() {
        if (list<T>::root == nullptr) {
            throw std::logic_error("no elements");
        }
        return list<T>::root->value;
    }

    template<class T>
    void list<T>::popStart() {
        if (list<T>::root == nullptr) {
            throw std::logic_error("no elements");
        }
        erase(list<T>::begin());
    }
        template<class T>
  void list<T>::popEnd() {
        if (list<T>::root == nullptr) {
            throw std::logic_error("no elements");
        }
        erase(list<T>::getTail(list<T>::begin()));
    }
    template<class T>
    void list<T>::add(const T &value) {
        forward_iterator it(end_node);
        std::unique_ptr<node> new_node(new node{value});
        if (it.ptr_) {
            new_node->parent = it.ptr_;
            it.ptr_->next = std::move(new_node);
        } else {
            new_node->next = nullptr;
            list<T>::root = std::move(new_node);
        }
        list<T>::end_node = getTail(root.get());
    }

}
#endif