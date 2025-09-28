#pragma once

#include "Person.h"

#include <string>
#include <vector>

class Instructor : public Person {
  private:
    std::string department_;
    std::vector<std::string> course_codes_;

  public:
    Instructor(int id, std::string name, std::string email, std::string department)
        : Person(id, std::move(name), std::move(email)), department_(std::move(department)) {}

    const std::string &department() const { return department_; }
    void set_department(const std::string &department) { department_ = department; }

    void assign_course(const std::string &course_code);
    const std::vector<std::string> &course_codes() const { return course_codes_; }

    std::string role() const override { return "Docente"; }
};
