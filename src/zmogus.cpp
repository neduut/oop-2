#include "Zmogus.h"

std::ostream& operator<<(std::ostream& os, const Zmogus& zmogus) {
    os << "Vardas: " << zmogus.firstName_ << ", Pavardė: " << zmogus.lastName_;
    return os;
}

std::istream& operator>>(std::istream& is, Zmogus& zmogus) {
    is >> zmogus.firstName_ >> zmogus.lastName_;
    return is;
}
