#pragma once

#include <string>

class Person {
  protected:
    int id_;
    std::string name_;
    std::string email_;

  public:
    Person(int id, std::string name, std::string email)
        : id_(id), name_(std::move(name)), email_(std::move(email)) {}
    virtual ~Person() = default;

    int id() const { return id_; }
    const std::string &name() const { return name_; }
    const std::string &email() const { return email_; }

    void set_name(const std::string &name) { name_ = name; }
    void set_email(const std::string &email) { email_ = email; }

    virtual std::string role() const = 0;
};
