#ifndef HASHER_POLYNOMIAL_H
#define HASHER_POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


template<typename T>
class Polynomial {
private:
    mutable std::vector<T> data;

    void remove_high_zero(std::vector<T> &v_data);

public:
    template<typename Iter>
    Polynomial<T>(Iter first, Iter last);

    Polynomial<T>(const Polynomial<T> &polynom);

    explicit Polynomial<T>(const T &num = T());

    explicit Polynomial<T>(const std::vector<T> &a);

    Polynomial<T>(std::initializer_list<T> l);

    const std::vector<T> &getData() const;

    long long degree() const;

    const T &operator[](size_t index) const;

    T &operator[](size_t index);

    Polynomial<T> &operator=(const Polynomial<T> &other) = default;

    Polynomial<T> &operator=(Polynomial<T> &&other) = default;

    bool operator==(const Polynomial<T> &other) const;

    bool operator!=(const Polynomial<T> &other) const;

    bool operator==(const T &num) const;

    bool operator!=(const T &num) const;

    Polynomial<T> &operator+=(const Polynomial<T> &other);

    Polynomial<T> &operator+=(const T &num);

    Polynomial<T> &operator-=(const Polynomial<T> &other);

    Polynomial<T> &operator-=(const T &num);

    Polynomial<T> &operator*=(const Polynomial<T> &other);

    Polynomial<T> &operator*=(const T &num);

    T operator()(const T &point) const;

    Polynomial<T> &operator/=(const Polynomial<T> &other);

    Polynomial<T> &operator/=(const T &num);

    Polynomial<T> &operator%=(const Polynomial<T> &other);

    Polynomial<T> &operator%=(const T &num);

    auto begin() const;

    auto begin();

    auto end() const;

    auto end();
};

template<typename T>
void Polynomial<T>::remove_high_zero(std::vector<T> &v_data) {
    int count = 0;
    for (auto iter = v_data.rbegin(); iter != v_data.rend() && *iter == T(0); ++iter, ++count);
    v_data.erase(v_data.end() - count, v_data.end());
}

template<typename T>
Polynomial<T>::Polynomial(const std::vector<T> &a) : data(a) {
    remove_high_zero(data);
}

template<typename T>
Polynomial<T>::Polynomial(std::initializer_list<T> l) : data(l) {
    remove_high_zero(data);
}

template<typename T>
template<typename Iter>
Polynomial<T>::Polynomial(Iter first, Iter last) : data(first, last) {
    remove_high_zero(data);
}

template<typename T>
Polynomial<T>::Polynomial(const Polynomial<T> &polynom) : data(polynom.data) {
    remove_high_zero(data);
}

template<typename T>
Polynomial<T>::Polynomial(const T &num) {
    data.push_back(num);
    remove_high_zero(data);
}

template<typename T>
const T &Polynomial<T>::operator[](size_t index) const {
    if (index >= data.size()) {
        data.resize(index + 1);
    }
    return data[index];
}

template<typename T>
T &Polynomial<T>::operator[](size_t index) {
    if (index >= data.size()) {
        data.resize(index + 1);
    }
    return data[index];
}

template<typename T>
const std::vector<T> &Polynomial<T>::getData() const {
    return data;
}

template<typename T>
long long Polynomial<T>::degree() const {
    if (data.empty()) {
        return -1;
    } else {
        long long degree = data.size() - 1;
        for (auto iter = data.rbegin(); iter != data.rend(); ++iter, --degree) {
            if (*iter != T(0)) {
                return degree;
            }
        }
    }
    return -1;
}

template<typename T>
bool Polynomial<T>::operator==(const Polynomial<T> &other) const {
    while (!other.data.empty() && other.data.back() == T(0)) other.data.pop_back();
    while (!data.empty() && data.back() == T(0)) data.pop_back();

    if (data.size() != other.data.size()) {
        return false;
    }
    for (size_t i = 0; i != data.size(); ++i) {
        if (data[i] != other[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Polynomial<T>::operator!=(const Polynomial<T> &other) const {
    return !(*this == other);
}

template<typename T>
bool Polynomial<T>::operator!=(const T &num) const {
    return !(*this == num);
}

template<typename T>
bool Polynomial<T>::operator==(const T &num) const {
    return data.size() == 1 && data[0] == num;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator+=(const Polynomial<T> &other) {
    data.resize(std::max(other.data.size(), data.size()), T(0));
    for (size_t i = 0; i != std::min(data.size(), other.data.size()); ++i) {
        data[i] += other.data[i];
    }
    remove_high_zero(data);
    return *this;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator+=(const T &num) {
    if (data.size() == 0) {
        data.resize(1);
    }
    data[0] += num;
    remove_high_zero(data);
    return *this;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator-=(const Polynomial<T> &other) {
    data.resize(std::max(other.data.size(), data.size()), T(0));
    for (size_t i = 0; i != std::min(data.size(), other.data.size()); ++i) {
        data[i] -= other.data[i];
    }
    remove_high_zero(data);
    return *this;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator-=(const T &num) {
    if (data.size() == 0) {
        data.resize(1);
    }
    data[0] -= num;
    remove_high_zero(data);
    return *this;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator*=(const Polynomial<T> &other) {
    std::vector<T> temp(data.size() + other.data.size(), T(0));
    for (size_t i = 0; i != data.size(); ++i) {
        for (size_t j = 0; j != other.data.size(); ++j) {
            temp[i + j] += data[i] * other.data[j];
        }
    }
    remove_high_zero(temp);
    *this = Polynomial(temp);
    return *this;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator*=(const T &num) {
    for (size_t i = 0; i != data.size(); ++i) {
        data[i] *= num;
    }
    remove_high_zero(data);
    return *this;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator/=(const Polynomial<T> &other) {
    Polynomial<T> priv(T(0));
    while (data.size() >= other.data.size()) {
        T num = data.back() / other.data.back();
        size_t degree = data.size() - other.data.size();
        std::vector<T> div(degree + 1);
        div.back() = num;
        Polynomial<T> temp(div);
        *this -= other * temp;
        priv += temp;
    }
    data = priv.data;
    return *this;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator/=(const T &num) {
    for (size_t i = 0; i != data.size(); ++i) {
        data[i] /= num;
    }
    remove_high_zero(data);
    return *this;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator%=(const Polynomial<T> &other) {
    Polynomial<T> quotient = *this / other;
    *this -= other * quotient;
    return *this;
}

template<typename T>
T Polynomial<T>::operator()(const T &point) const {
    T ans = T(0);
    for (auto iter = data.rbegin(); iter != data.rend(); ++iter) {
        ans += *iter;
        if ((iter + 1) != data.rend()) {
            ans *= point;
        }
    }
    return ans;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator%=(const T &num) {
    for (size_t i = 0; i != data.size(); ++i) {
        data[i] %= num;
    }
    remove_high_zero(data);
    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const Polynomial<T> &pol) {
    bool first_was = false;
    unsigned long long degree = pol.getData().size() - 1;
    for (auto iter = pol.getData().rbegin(); iter != pol.getData().rend(); ++iter, --degree) {
        T num = *iter;
        if (num != T(0)) {
            if (num > T(0) && first_was) {
                out << '+';
            }

            first_was = true;
            if (degree == 0) {
                out << num;
            } else if (num == T(1)) {
                out << 'x';
            } else if (num == T(-1)) {
                out << "-x";
            } else {
                out << num << "*x";
            }
            if (degree > 1) {
                out << "^{" << degree << '}';
            }
        }
    }
    if (pol.getData().size() == 0) {
        out << 0;
    }
    return out;
}

template<typename T>
auto Polynomial<T>::begin() const {
    return data.cbegin();
}

template<typename T>
auto Polynomial<T>::begin() {
    return data.begin();
}

template<typename T>
auto Polynomial<T>::end() const {
    return data.cend();
}

template<typename T>
auto Polynomial<T>::end() {
    return data.end();
}

template<typename T>
Polynomial<T> operator*(Polynomial<T> first, const Polynomial<T> &second) {
    return first *= second;
}

template<typename T>
Polynomial<T> operator*(Polynomial<T> polynom, const T &num) {
    return polynom *= num;
}

template<typename T>
Polynomial<T> operator*(const T &num, Polynomial<T> polynom) {
    return polynom *= num;
}

template<typename T>
Polynomial<T> operator+(Polynomial<T> first, const Polynomial<T> &second) {
    return first += second;
}

template<typename T>
Polynomial<T> operator+(Polynomial<T> polynom, const T &num) {
    return polynom += num;
}

template<typename T>
Polynomial<T> operator+(const T &num, Polynomial<T> polynom) {
    return polynom += num;
}

template<typename T>
Polynomial<T> operator-(Polynomial<T> first, const Polynomial<T> &second) {
    return first -= second;
}

template<typename T>
Polynomial<T> operator-(Polynomial<T> polynom, const T &num) {
    return polynom -= num;
}

template<typename T>
Polynomial<T> operator-(const T &num, Polynomial<T> polynom) {
    return (polynom *= -1) += num;
}

template<typename T>
Polynomial<T> operator/(Polynomial<T> first, const Polynomial<T> &second) {
    return first /= second;
}

template<typename T>
Polynomial<T> operator/(Polynomial<T> polynom, const T &num) {
    return polynom /= num;
}

template<typename T>
Polynomial<T> operator%(Polynomial<T> first, const Polynomial<T> &second) {
    return first %= second;
}

template<typename T>
Polynomial<T> operator%(Polynomial<T> polynom, const T &num) {
    return polynom %= num;
}

#endif //HASHER_POLYNOMIAL_H