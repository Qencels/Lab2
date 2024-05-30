#pragma once
#include <iostream>
#include "TParserBaseListener.h"
#include "TParser.h"
#include "TLexer.h"
#include "Polynomial.h"
#include "List.h"
#include "Monom.h"
#include <stack> 
#include <map>
#include <string>
#include <unordered_map>

namespace antlrcpptest {
    class CalculatorInterpreter : public TParserBaseListener {

        std::stack<Polynomial<int>> polynomial_stack;
        std::stack<std::string> var_stack;
        std::stack<std::string> mon_var;
        std::stack<int> integ;

        std::map<std::string, Polynomial<int>> parameters;

        int X, Y, Z;

    public:
        CalculatorInterpreter() : X(0), Y(0), Z(0) {}
        
        void exitPlusOp(TParser::PlusOpContext* ctx) override {
            auto r = polynomial_stack.top(); polynomial_stack.pop();
            auto l = polynomial_stack.top(); polynomial_stack.pop();
            polynomial_stack.push(l + r);
        };
        void exitBinaryMinusOp(TParser::BinaryMinusOpContext* ctx) override {
            auto r = polynomial_stack.top(); polynomial_stack.pop();
            auto l = polynomial_stack.top(); polynomial_stack.pop();
            polynomial_stack.push(l - r);
        };
        void exitUnaryMinusOp(TParser::UnaryMinusOpContext* ctx) override {
            polynomial_stack.top() = polynomial_stack.top() * (-1);
        };
        void exitMultOp(TParser::MultOpContext* ctx) override {
            auto r = polynomial_stack.top(); polynomial_stack.pop();
            auto l = polynomial_stack.top(); polynomial_stack.pop();
            polynomial_stack.push(l * r);
        };
        void exitSetValue(TParser::SetValueContext* ctx) override 
        {
            auto cur = polynomial_stack.top();
            std::string var_name = var_stack.top();
            std::pair<std::string, Polynomial<int>> pair(var_name, cur);
            parameters.erase(var_name);
            parameters.insert(pair);
            polynomial_stack.pop();
            var_stack.pop();
        };

        void enterSetValue(TParser::SetValueContext* ctx) override {};
        void exitGetValue(TParser::GetValueContext* ctx) override
        {
            std::string var_name = var_stack.top();
            var_stack.pop();
            try {
                Polynomial<int> cur = parameters.at(var_name);
                polynomial_stack.push(cur);
            }
            catch (std::out_of_range)
            {
                std::string message = var_name + " not find";
                throw std::out_of_range(message);
            }
        };
        void exitConvertToInt(TParser::ConvertToIntContext* ctx) override
        {
            integ.push(std::stoi(ctx->getText()));
        };

        void exitRUsrVar(TParser::RUsrVarContext* ctx) override
        {
            var_stack.push(ctx->getText());
        }

        virtual void exitPrint(TParser::PrintContext* ) override
        {
            std::cout << polynomial_stack.top() << std::endl;
            polynomial_stack.pop();
        }

        void exitRVar(TParser::RVarContext* ctx) override
        {
            mon_var.push(ctx->getText());
        }

        void exitPow(TParser::PowContext* ) override 
        {
            int pow = integ.top();
            std::string var = mon_var.top();

            if (var == "x") { X += pow; }
            if (var == "y") { Y += pow; }
            if (var == "z") { Z += pow; }

            integ.pop();
            mon_var.pop();
        };

        void enterMonom(TParser::MonomContext* ) override {
            X = Y = Z = 0;
        }
        void exitMonom(TParser::MonomContext* ) override {}

        void enterFullMonom(TParser::FullMonomContext* ) override {}

        virtual void exitFullMonom(TParser::FullMonomContext* ) override
        {
            int coeff = integ.top();
            integ.pop();
            Polynomial<int> pol;

            std::unordered_map<char, int> vars = {{'x', X},{'y', Y},{'z', Z}};
            pol.push(Monom<int>(coeff, vars));

            polynomial_stack.push(pol);
        }
        void exitMonomZeroPower(TParser::MonomZeroPowerContext* ) override
        {
            int coeff = integ.top();
            integ.pop();
            Polynomial<int> pol;

            std::unordered_map<char, int> vars = {{'x', X},{'y', Y},{'z', Z}};
            pol.push(Monom<int>(coeff, vars));

            polynomial_stack.push(pol);
        }
        void enterMonomWithouCoefficient(TParser::MonomWithouCoefficientContext* ) override
        {
            int coeff = 1;
            Polynomial<int> pol;

            std::unordered_map<char, int> vars = {{'x', X},{'y', Y},{'z', Z}};
            pol.push(Monom<int>(coeff, vars));

            polynomial_stack.push(pol);
        }
        void exitCalculate(TParser::CalculateContext* ) override
        {
            int x_point = integ.top();
            integ.pop();
            int y_point = integ.top();
            integ.pop();
            int z_point = integ.top();
            integ.pop();
            Polynomial<int> cur = polynomial_stack.top();
            int result = cur.calc(x_point, y_point, z_point);
            std::cout << "Calculate at point B(" << x_point << ", " << y_point << ", " << z_point << ") = " << result << std::endl;
            polynomial_stack.pop();
        }
    };
}

