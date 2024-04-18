#include "tasks.h"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <unordered_set>
#include <utility>

std::ostream &operator<<(std::ostream &os, const Student &student) {
    os << student.name;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Exam &exam) {
    os << exam.subject;
    return os;
}

Score calculate_score(Student student, Exam exam) {
    int math_diff = static_cast<int>(student.math_skill) *
                    std::max(1, 100 - static_cast<int>(exam.math_difficulty));
    int coding_diff =
        static_cast<int>(student.coding_skill) *
        std::max(1, 100 - static_cast<int>(exam.coding_difficulty));

    int diff = math_diff + coding_diff;
    return diff / 50;
}

std::vector<std::pair<Student, Score>> find_best_n_students(
    std::vector<Student> students, const Exam &exam, size_t n) {
    std::vector<std::pair<Student, Score>> result;

    std::transform(
        students.cbegin(), students.cend(), std::back_inserter(result),
        [&exam](const Student &student) -> std::pair<Student, Score> {
            return std::make_pair(student, calculate_score(student, exam));
        });

    std::sort(
        result.begin(), result.end(),
        [](const std::pair<Student, Score> &a,
           const std::pair<Student, Score> &b) { return a.second > b.second; });

    return std::vector<std::pair<Student, Score>>(
        result.begin(), result.begin() + std::min(n, result.size()));
}

size_t max_score_difference(const std::vector<Student> &students,
                            const std::vector<Exam> &exams) {
    if (students.empty() || exams.empty()) {
        return 0;
    }

    auto tmp = std::vector<size_t>();

    std::transform(
        exams.cbegin(), exams.cend(), std::back_inserter(tmp),
        [&students](const Exam &exam) -> size_t {
            auto scores_pairs =
                find_best_n_students(students, exam, students.size());

            auto scores = std::vector<Score>();

            std::transform(
                scores_pairs.cbegin(), scores_pairs.cend(),
                std::back_inserter(scores),
                [](const auto &pair) -> Score { return pair.second; });

            int result = 0;

            for (auto it = scores.cbegin(); it + 1 != scores.cend(); it++) {
                if (*(it) - *(it + 1) > result) {
                    result = *(it) - *(it + 1);
                }
            }

            return static_cast<size_t>(result);
        });

    return *std::max_element(tmp.cbegin(), tmp.cend());
}

std::pair<std::unordered_set<Student>, std::unordered_set<Student>>
filter_students(const std::vector<Student> &students,
                const std::vector<Exam> &exams) {
    auto s1 = std::unordered_set<Student>();
    auto s2 = std::unordered_set<Student>();

    std::for_each(
        students.cbegin(), students.cend(),
        [&exams, &s1, &s2](const Student &student) {
            if (exams.empty()) {
                s1.insert(student);
                return;
            }

            auto scores = std::vector<Score>();
            std::transform(exams.cbegin(), exams.cend(),
                           std::back_inserter(scores),
                           [&student](const Exam &exam) {
                               return calculate_score(student, exam);
                           });

            if (*std::min_element(scores.cbegin(), scores.cend()) >= 100) {
                s1.insert(student);
            }

            if (*std::max_element(scores.cbegin(), scores.cend()) >= 100) {
                s2.insert(student);
            }
        });

    return std::make_pair(s1, s2);
}

auto order_scores = [](const auto &a, const auto &b) {
    if (a.second > b.second) {
        return true;
    } else if (a.second == b.second) {
        return a < b;
    } else {
        return false;
    }
};

Leaderboard get_leaderboard_of_each_subject(
    const std::vector<Student> &students, const std::vector<Exam> &exams) {
    auto leaderboard = Leaderboard();

    std::for_each(
        exams.cbegin(), exams.cend(),
        [&students, &leaderboard](const Exam &exam) {
            auto scores = std::vector<std::pair<Student, Score>>();
            std::transform(
                students.cbegin(), students.cend(), std::back_inserter(scores),
                [&exam](const Student &student) -> std::pair<Student, Score> {
                    return std::make_pair(student,
                                          calculate_score(student, exam));
                });
            std::sort(scores.begin(), scores.end(), order_scores);

            if (leaderboard.count(exam.subject)) {
                auto &tmp = leaderboard.at(exam.subject);
                auto score_map = std::unordered_map<Student, Score>();

                auto vec_to_map =
                    [&score_map](const std::pair<Student, Score> &pair) {
                        if (score_map.count(pair.first)) {
                            auto &score = score_map.at(pair.first);
                            score += pair.second;
                        } else {
                            score_map.insert({pair});
                        }
                    };

                std::for_each(tmp.cbegin(), tmp.cend(), vec_to_map);
                std::for_each(scores.cbegin(), scores.cend(), vec_to_map);

                tmp = std::vector<std::pair<Student, Score>>();
                std::transform(
                    score_map.cbegin(), score_map.cend(),
                    std::back_inserter(tmp),
                    [&score_map](const std::pair<Student, Score> &pair) {
                        return pair;
                    });
                std::sort(tmp.begin(), tmp.end(), order_scores);
            } else {
                leaderboard.insert({exam.subject, scores});
            }
        });

    return leaderboard;
}
