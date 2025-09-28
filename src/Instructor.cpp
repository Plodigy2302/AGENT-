#include "Instructor.h"

#include <algorithm>

void Instructor::assign_course(const std::string &course_code) {
    if (std::find(course_codes_.begin(), course_codes_.end(), course_code) == course_codes_.end()) {
        course_codes_.push_back(course_code);
    }
}
