#pragma once

#include <string>

class Enrollment {
  private:
    int student_id_;
    std::string course_code_;
    std::string status_;

  public:
    Enrollment(int student_id, std::string course_code, std::string status)
        : student_id_(student_id), course_code_(std::move(course_code)), status_(std::move(status)) {}

    int student_id() const { return student_id_; }
    const std::string &course_code() const { return course_code_; }
    const std::string &status() const { return status_; }

    void set_status(const std::string &status) { status_ = status; }
};
