#pragma once

#include "Person.h"

#include <map>
#include <string>
#include <vector>

class Enrollment;

class Student : public Person {
  private:
    std::string major_;
    std::map<std::string, double> grades_; // course code -> grade

  public:
    Student(int id, std::string name, std::string email, std::string major)
        : Person(id, std::move(name), std::move(email)), major_(std::move(major)) {}

    const std::string &major() const { return major_; }
    void set_major(const std::string &major) { major_ = major; }

    void record_grade(const std::string &course_code, double grade);
    [[nodiscard]] double calculate_gpa() const;

    std::string role() const override { return "Estudiante"; }
};
