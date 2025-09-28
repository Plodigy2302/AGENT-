#pragma once

#include <functional>
#include <memory>
#include <utility>

template <typename T> class DoublyLinkedList {
  private:
    struct Node {
        T value;
        std::unique_ptr<Node> next;
        Node *prev;
        explicit Node(T v) : value(std::move(v)), next(nullptr), prev(nullptr) {}
    };

    std::unique_ptr<Node> head_;
    Node *tail_ = nullptr;
    std::size_t size_ = 0;

  public:
    DoublyLinkedList() = default;

    void push_front(T value) {
        auto node = std::make_unique<Node>(std::move(value));
        node->next = std::move(head_);
        if (node->next) {
            node->next->prev = node.get();
        } else {
            tail_ = node.get();
        }
        head_ = std::move(node);
        ++size_;
    }

    template <typename Predicate, typename Factory> void insert_after(Predicate predicate, Factory factory) {
        Node *current = head_.get();
        while (current) {
            if (predicate(current->value)) {
                auto node = std::make_unique<Node>(factory(current->value));
                node->prev = current;
                node->next = std::move(current->next);
                if (node->next) {
                    node->next->prev = node.get();
                } else {
                    tail_ = node.get();
                }
                current->next = std::move(node);
                ++size_;
                return;
            }
            current = current->next.get();
        }
    }

    template <typename Predicate> void remove_if(Predicate predicate) {
        Node *current = head_.get();
        while (current) {
            if (predicate(current->value)) {
                if (current->prev) {
                    current->prev->next = std::move(current->next);
                    if (current->prev->next) {
                        current->prev->next->prev = current->prev;
                    } else {
                        tail_ = current->prev;
                    }
                } else {
                    head_ = std::move(current->next);
                    if (head_) {
                        head_->prev = nullptr;
                    } else {
                        tail_ = nullptr;
                    }
                }
                --size_;
                return;
            }
            current = current->next.get();
        }
    }

    template <typename Func> void for_each_reverse(Func func) const {
        Node *current = tail_;
        while (current) {
            func(current->value);
            current = current->prev;
        }
    }

    std::size_t size() const { return size_; }

    template <typename Compare> void cocktail_sort(Compare compare) {
        if (!head_ || !head_->next) {
            return;
        }
        bool swapped = true;
        Node *start = head_.get();
        Node *end = tail_;
        while (swapped) {
            swapped = false;
            for (Node *current = start; current && current->next && current != end; current = current->next.get()) {
                if (!compare(current->value, current->next->value)) {
                    std::swap(current->value, current->next->value);
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
            swapped = false;
            end = end ? end->prev : nullptr;
            for (Node *current = end; current && current->prev && current != start; current = current->prev) {
                if (!compare(current->prev->value, current->value)) {
                    std::swap(current->prev->value, current->value);
                    swapped = true;
                }
            }
            start = start ? start->next.get() : nullptr;
        }
    }
};
