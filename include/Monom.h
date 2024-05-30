#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

template <class type>
class Monom {
private:
    std::unordered_map<char, type> vars;

public:
    static void GapsTransform(std::string& str) {
        int i = 0;
        while (str.find(' ') != -1) {
            i = str.find(' ');
            str.erase(i, 1);
        }
    }

    type coef;

	Monom(double coefficient = 0.0, const std::unordered_map<char, type>& variables = {}) : coef((type)coefficient), vars(variables) {}

    std::unordered_map<char, type> GetVars() const {
        return vars;
    }

    type GetCoef() const {
        return coef;
    }

	Monom<type> operator+(const Monom<type>& obj) {
        if (vars != obj.vars) throw std::invalid_argument("Invalid degrees or variable names!");
        return Monom<type>(this->coef + obj.coef, this->vars);
	}

    Monom<type> operator-(const Monom<type>& obj) {
        if (vars != obj.vars) throw std::invalid_argument("Invalid degrees or variable names!");
        return Monom<type>(this->coef - obj.coef, this->vars);
    }

    bool operator==(const Monom<type>& obj) {
        if (coef != obj.coef) return false;
        if (vars != obj.vars) return false;
        return true;
    }

    bool operator!=(const Monom<type>& obj) {
        if (coef == obj.coef) return false;
        if (vars == obj.vars) return false;
        return true;
    }

    Monom<type> operator*(const Monom& obj) const {
        Monom<type> res = *this;
        res.coef *= obj.coef;

        for (const auto& elem : obj.vars) {
            res.vars[elem.first] += elem.second;
        }

        return res;
    }

    Monom& operator=(const Monom<type>& obj) {
        this->coef = obj.coef;
        this->vars = obj.vars;
		return *this;
    }

    template <class k>
    friend std::ostream& operator<<(std::ostream& stream, const Monom<k>& obj) {
        stream << obj.coef;
        for (const auto& elem : obj.vars) {
            stream << "*" << elem.first << "^" << elem.second;
        }
        return stream;
    }

    template <class k>
    friend std::istream& operator>>(std::istream& stream, Monom<k>& obj) {
        std::string tmp_str = "";
        std::getline(stream, tmp_str, '*');
        GapsTransform(tmp_str);

        try {
            obj.coef = (type)std::stod(tmp_str); // get coef from string
        }
        catch (...) {
            throw std::invalid_argument("Invalid argument!");
        }

        while (std::getline(stream, tmp_str, '*')) {
            GapsTransform(tmp_str);
            char name = tmp_str[0];
            type degree;
            try {
                degree = (type)std::stod(tmp_str.substr(2));
            }
            catch (...) {
                throw std::invalid_argument("Invalid argument!");
            }
            obj.vars[name] = degree;
        }
        return stream;
    }

    ~Monom() {}

};
