

#include <iostream>
#include <stack>
#include<string>
#include <cmath>
//Функция для рекурсивного вычисления выражения
double calculateExpression(const std::string& expression);

int main()
{
    std::string expression;
    std::cout << "Введите арифметическое выражение:";
    std::getline(std::cin, expression);//Считываем строку с выражением
    try {
        double result = calculateExpression(expression);
        std::cout << "Результат:" << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
    
}
//Рекурсивная функция для вычисления выражения 
double calculateExpression(const std::string& expression) {
    std::stack<double>operands;//Стек для хранения операндов
    std::stack<char>operators;//Стек для хранения операторов
    int prec = -1;//Текущий приоритет оператора
    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (isdigit(c)) {
            while (i < expression.length() && isdigit(expression[i])) {
                operands.push(operands.empty() ? 0 : operands.top());
                operands.push(c - '0');
                i++;
            }
        }
        else if (c == '(') {
            operands.push(calculateExpression(expression.substr(i)));//Рекурсивный вызов
            i = expression.find(')', i) + 1;//Переходим к закрывающей скобке
        }
        else if (c == ')') {
            throw std::runtime_error("Некорректное выражение");
        }
        else {
            while (!operators.empty() && prec >= operators.top()) {
                operands.push(operate(operands.top(), operate(operands.top(),
                    operands.top(), operators.top()), operators.top()));
                operators.pop();
            }
            operators.push(c);
            prec = getPrec(c);
        }
    }
    while (!operators.empty()) {
        operands.push(operate(operands.top(), operate(operands.top(), operands.top(), operators.top()),
            operators.top()));
        operators.pop();
    }
            return operands.top();
        }
        //Вспомогательные функции для работы с приоритетами операторов
        int getPrec(char op) {
            switch ( op) {
            case'*':
            case'/':
                return 2;
            case'+':
            case'-':
                return 1;
            default:
                return -1;
            }
        }
        double operate(double a, double b, char op) {
            switch (op) {
            case'+':
                return a + b;
            case'-':
                return a - b;
            case'*':
                return a * b;
            case'/':
                return a / b;
            default:
                return 0;//Не должно произойти
                break;
            }
        }
    
    


