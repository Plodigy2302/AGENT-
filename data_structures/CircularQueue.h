#pragma once

#include <stdexcept>
#include <utility>
#include <vector>

template <typename T> class CircularQueue {
  private:
    std::vector<T> buffer_;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t size_ = 0;

  public:
    explicit CircularQueue(std::size_t capacity) : buffer_(capacity) {}

    bool empty() const { return size_ == 0; }
    bool full() const { return size_ == buffer_.size(); }
    std::size_t size() const { return size_; }

    void enqueue(T value) {
        if (full()) {
            throw std::runtime_error("Cola circular llena");
        }
        buffer_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % buffer_.size();
        ++size_;
    }

    T dequeue() {
        if (empty()) {
            throw std::runtime_error("Cola circular vacía");
        }
        T value = std::move(buffer_[head_]);
        head_ = (head_ + 1) % buffer_.size();
        --size_;
        return value;
    }

    void rotate(std::size_t steps) {
        if (empty()) {
            return;
        }
        steps %= size_;
        for (std::size_t i = 0; i < steps; ++i) {
            enqueue(dequeue());
        }
    }

    template <typename Func> void for_each(Func func) const {
        for (std::size_t i = 0; i < size_; ++i) {
            std::size_t index = (head_ + i) % buffer_.size();
            func(buffer_[index]);
        }
    }
};
