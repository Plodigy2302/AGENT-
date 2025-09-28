#include "Student.h"

#include <numeric>

void Student::record_grade(const std::string &course_code, double grade) {
    grades_[course_code] = grade;
}

double Student::calculate_gpa() const {
    if (grades_.empty()) {
        return 0.0;
    }
    double sum = std::accumulate(grades_.begin(), grades_.end(), 0.0,
                                 [](double acc, const auto &pair) { return acc + pair.second; });
    return sum / static_cast<double>(grades_.size());
}
