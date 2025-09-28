#pragma once

#include <string>
#include <vector>

class Assignment;

class Course {
  private:
    std::string code_;
    std::string title_;
    int credits_;
    int instructor_id_;

  public:
    Course(std::string code, std::string title, int credits, int instructor_id)
        : code_(std::move(code)), title_(std::move(title)), credits_(credits), instructor_id_(instructor_id) {}

    const std::string &code() const { return code_; }
    const std::string &title() const { return title_; }
    int credits() const { return credits_; }
    int instructor_id() const { return instructor_id_; }

    void set_title(const std::string &title) { title_ = title; }
    void set_instructor(int instructor_id) { instructor_id_ = instructor_id; }
};
