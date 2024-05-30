#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "Monom.h"
#include "List.h"

template <class type>
class Polynomial {
public:
    List<Monom<type>> monoms;
    Polynomial() {}
    ~Polynomial() {}

    void push(const Monom<type>& obj) {
        bool flag = false;

        for (auto it = monoms.Begin(); it != monoms.End(); it++) {
            if (it->GetVars() == obj.GetVars()) {
                it->coef += obj.coef;
                if (it->coef == 0) { monoms.Erase(it); }
                flag = true;
                break;
            }
        }

        if (!flag && obj.coef != 0) { monoms.PushBack(obj); }
    }

    bool operator==(const Polynomial& obj) {
        size_t counterSrc = 0;
        size_t counterTrg = 0;
        for (auto i = this->monoms.Begin(); i != this->monoms.End(); i++) counterSrc++;
        for (auto i = obj.monoms.Begin(); i != obj.monoms.End(); i++) counterTrg++;
        if (counterSrc != counterTrg) return false;

        for (auto i = this->monoms.Begin(); i != this->monoms.End(); i++) {
            for (auto k = obj.monoms.Begin(); k != obj.monoms.End(); k++) {
                if (*i == *k) {
                    counterSrc--;
                    break;
                }
            }
        }

        return !counterSrc;
    }

    bool operator!=(const Polynomial& obj) {
        return !(*this==obj);
    }

    Polynomial<type> operator+(const Polynomial<type>& obj) {
        Polynomial<type> res = *this;
        for (auto it = obj.monoms.Begin(); it != obj.monoms.End(); it++) {
            res.push(*it);
        }
        return res;
    }

    Polynomial<type> operator-(const Polynomial<type>& obj) {
        Polynomial<type> res = *this;
        for (auto it = obj.monoms.Begin(); it != obj.monoms.End(); it++) {
            Monom<type> alt_monom = *it;
            alt_monom.coef = -alt_monom.coef;
            res.push(alt_monom);
        }
        return res;
    }

    Polynomial<type> operator*(const Polynomial<type>& obj) {
        Polynomial<type> res;
        for (auto it = monoms.Begin(); it != monoms.End(); it++) {
            for (auto k = obj.monoms.Begin(); k != obj.monoms.End(); k++) {
                Monom<type> comp = (*it) * (*k);
                res.push(comp);
            }
        }
        return res;
    }

    Polynomial<type> operator*(type value) {
        Polynomial<type> res;
        for (auto it = monoms.Begin(); it != monoms.End(); it++) {
            Monom<type> temp = *it;
            temp.coef *= value;
            res.push(temp);
        }
        return res;
    }

    template <class K>
    friend std::ostream& operator<<(std::ostream& ostr, const Polynomial<K>& obj) {
        auto it = obj.monoms.Begin();
        if (it != obj.monoms.End()) {
            ostr << *it;
            ++it;
        }
        while (it != obj.monoms.End()) {
            ostr << " + " << *it;
            ++it;
        }
        return ostr;
    }

    const std::string GetPolynomial() const {
        std::string res = "";
        std::string tmp = "";
        auto stream = std::stringstream(tmp);
        auto it = monoms.Begin();
        if (it != monoms.End()) {
            stream << *it;
            ++it;
        }
        while (it != monoms.End()) {
            stream << "+" << *it;
            ++it;
        }
        stream >> res;
        return res;
    }

    bool ValidCheck(const std::string& str) {
        for (char symbol : str) {
            if (!std::isdigit(symbol) && !std::isalpha(symbol) && symbol != '-' && symbol != '+' && symbol != '*' && symbol != '^' && symbol != '.') { return false; }
        }
        return true;
    }

    type calc(type x, type y, type z) const {
		double result = 0.0;
        for (auto it = monoms.Begin(); it != monoms.End(); it++) {
			double monVal = it.target->value.GetCoef();
            auto vr = it.target->value.GetVars();
			monVal *= pow(x, vr.at('x'));
			monVal *= pow(y, vr.at('y'));
			monVal *= pow(z, vr.at('z'));
			result += monVal;
		}
		return result;
	}

    friend std::istream& operator>>(std::istream& istr, Polynomial& obj) {
        std::string str;

        std::getline(istr, str);
        Monom<type>::GapsTransform(str);
        if (!obj.ValidCheck(str)) { throw std::invalid_argument("Invalid args!"); }

        std::string tmp_str = "";

        if (str[0] == '-') {
            tmp_str = "-";
            str = str.substr(1);
        }

        for (char symbol : str) {
            Monom<type> monom;
            std::istringstream str_stream(tmp_str);

            if (symbol == '-') {
                str_stream >> monom;
                obj.push(monom);
                tmp_str = "-";
            } else if (symbol == '+') {
                str_stream >> monom;
                obj.push(monom);
                tmp_str = "";
            } else {
                tmp_str += symbol;
            }
        }

        Monom<type> monom;
        std::istringstream str_stream(tmp_str);
        str_stream >> monom;
        obj.push(monom);

        return istr;
    }
};
