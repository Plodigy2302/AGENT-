#pragma once

#include <string>
#include <utility>

class Assignment {
  private:
    std::string title_;
    std::string description_;
    std::string due_date_;

  public:
    Assignment() = default;
    Assignment(std::string title, std::string description, std::string due_date)
        : title_(std::move(title)), description_(std::move(description)), due_date_(std::move(due_date)) {}

    const std::string &title() const { return title_; }
    const std::string &description() const { return description_; }
    const std::string &due_date() const { return due_date_; }
};
