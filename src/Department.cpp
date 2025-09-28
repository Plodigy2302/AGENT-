#include "Department.h"

#include <algorithm>

void Department::add_instructor(int instructor_id) {
    if (std::find(instructor_ids_.begin(), instructor_ids_.end(), instructor_id) == instructor_ids_.end()) {
        instructor_ids_.push_back(instructor_id);
    }
}
