#pragma once

#include <string>
#include <vector>

class Department {
  private:
    std::string name_;
    std::vector<int> instructor_ids_;

  public:
    explicit Department(std::string name) : name_(std::move(name)) {}

    const std::string &name() const { return name_; }
    const std::vector<int> &instructor_ids() const { return instructor_ids_; }

    void add_instructor(int instructor_id);
};
