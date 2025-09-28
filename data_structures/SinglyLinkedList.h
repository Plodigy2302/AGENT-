#pragma once

#include <functional>
#include <memory>
#include <utility>

template <typename T> class SinglyLinkedList {
  private:
    struct Node {
        T value;
        std::unique_ptr<Node> next;
        explicit Node(T v) : value(std::move(v)), next(nullptr) {}
    };

    std::unique_ptr<Node> head_;
    Node *tail_ = nullptr;
    std::size_t size_ = 0;

    static std::unique_ptr<Node> merge(std::unique_ptr<Node> left, std::unique_ptr<Node> right,
                                       const std::function<bool(const T &, const T &)> &cmp) {
        std::unique_ptr<Node> result;
        Node *result_tail = nullptr;

        auto push = [&](std::unique_ptr<Node> &source) {
            if (!result) {
                result = std::move(source);
                result_tail = result.get();
            } else {
                result_tail->next = std::move(source);
                result_tail = result_tail->next.get();
            }
        };

        while (left && right) {
            if (cmp(left->value, right->value)) {
                auto next = std::move(left->next);
                push(left);
                left = std::move(next);
            } else {
                auto next = std::move(right->next);
                push(right);
                right = std::move(next);
            }
        }

        auto append_remaining = [&](std::unique_ptr<Node> &remaining) {
            while (remaining) {
                auto next = std::move(remaining->next);
                push(remaining);
                remaining = std::move(next);
            }
        };

        append_remaining(left);
        append_remaining(right);

        return result;
    }

    static std::unique_ptr<Node> merge_sort_impl(std::unique_ptr<Node> head,
                                                 const std::function<bool(const T &, const T &)> &cmp) {
        if (!head || !head->next) {
            return head;
        }

        Node *slow = head.get();
        Node *fast = head->next.get();
        while (fast && fast->next) {
            slow = slow->next.get();
            fast = fast->next->next.get();
        }

        std::unique_ptr<Node> right = std::move(slow->next);
        std::unique_ptr<Node> left = std::move(head);
        left = merge_sort_impl(std::move(left), cmp);
        right = merge_sort_impl(std::move(right), cmp);

        return merge(std::move(left), std::move(right), cmp);
    }

    void rebuild_tail() {
        tail_ = head_.get();
        while (tail_ && tail_->next) {
            tail_ = tail_->next.get();
        }
    }

  public:
    SinglyLinkedList() = default;

    void push_back(T value) {
        auto node = std::make_unique<Node>(std::move(value));
        if (!head_) {
            head_ = std::move(node);
            tail_ = head_.get();
        } else {
            tail_->next = std::move(node);
            tail_ = tail_->next.get();
        }
        ++size_;
    }

    template <typename Predicate> void remove_if(Predicate predicate) {
        Node *prev = nullptr;
        auto *current_ptr = &head_;
        while (*current_ptr) {
            if (predicate((*current_ptr)->value)) {
                auto removed = std::move(*current_ptr);
                if (prev) {
                    *current_ptr = std::move(removed->next);
                } else {
                    head_ = std::move(removed->next);
                }
                --size_;
                continue;
            }
            prev = current_ptr->get();
            current_ptr = &((*current_ptr)->next);
        }
        rebuild_tail();
    }

    template <typename Func> void for_each(Func func) {
        Node *current = head_.get();
        while (current) {
            func(current->value);
            current = current->next.get();
        }
    }

    template <typename Func> void for_each(Func func) const {
        const Node *current = head_.get();
        while (current) {
            func(current->value);
            current = current->next.get();
        }
    }

    std::size_t size() const { return size_; }

    template <typename Compare> void sort(Compare compare) {
        if (!head_ || !head_->next) {
            return;
        }
        head_ = merge_sort_impl(std::move(head_),
                                std::function<bool(const T &, const T &)>(compare));
        rebuild_tail();
    }
};
