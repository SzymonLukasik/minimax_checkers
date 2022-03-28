#ifndef CRABSQUARED_CHECKERS_UTILS_H
#define CRABSQUARED_CHECKERS_UTILS_H

/*
    Converts pos to square name.
    Eg: (1,2) -> "C2"
        (3,5) -> "F4"
*/
inline std::string sqtostr(square_t sq)
{
    return {char(sq.second + char('A')), char(sq.first + char('1'))};
}

std::ostream &operator<<(std::ostream &os, square_t sq)
{
    os << sqtostr(sq);
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& x) {
    os << "[|";
    if (!x.empty()) {
        for (auto it=x.begin(); it != std::prev(x.end()); ++it) {
            os << *it << ", ";
        }
        auto it = std::prev(x.end());
        os << *it;
    }
    os << "|]";
    return os;
}

template <typename U, typename V>
std::ostream& operator<< (std::ostream& os, const std::pair<U, V>& x) {
    os << '<' << x.first << ", " << x.second << '>';
    return os;
}

template <typename U, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<U, V>& x)
{
    os << '{';
    if (x.size() > 0) {
        for (auto it=x.begin(); it != std::prev(x.end()); ++it) {
            os << it->first << ": " << it->second << ", ";
        }
        auto it = std::prev(x.end());
        os << it->first << ": " << it->second;
    }
    os << '}';
    return os;
}

#endif //CRABSQUARED_CHECKERS_UTILS_H
