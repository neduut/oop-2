#pragma once
#include <iostream>
#include <string>

class Zmogus {
protected:
    std::string firstName_;
    std::string lastName_;

public:
    Zmogus() : firstName_(""), lastName_("") {}
    Zmogus(const std::string& firstName, const std::string& lastName)
        : firstName_(firstName), lastName_(lastName) {}

    virtual ~Zmogus() = default; // virtual destructor

    // abstract class interface
    virtual std::istream& read(std::istream& is) = 0;
    virtual std::ostream& print(std::ostream& os) const = 0;

    // getters/setters
    std::string getFirstName() const { return firstName_; }
    std::string getLastName() const { return lastName_; }
    void setFirstName(const std::string& firstName) { firstName_ = firstName; }
    void setLastName(const std::string& lastName) { lastName_ = lastName; }

    // operators
    friend std::istream& operator>>(std::istream& is, Zmogus& zmogus) {
        return zmogus.read(is);
    }

    friend std::ostream& operator<<(std::ostream& os, const Zmogus& zmogus) {
        return zmogus.print(os);
    }
};