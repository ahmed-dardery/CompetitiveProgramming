double integral(double(*f)(double), double a, double b, int n = 10) {
    double h = (b - a) / n;
    double h2 = 0.5 * h;
    double bound = a + (n - 0.25) * h;
    double intg = f(a) + 4.0 * f(a + h2);

    for (a += h; a < bound; a += h)
        intg += 2.0 * f(a) + 4.0 * f(a + h2);

    return h * (intg + f(a)) / 6;
}

struct func {
    enum OPS {
        OPEN = -11, CLOSE, PLUS, MINUS, MUL, DIV, X = 0
    };
    vector<int> postfix;
    vector<double> constants = {0};

    func() {}

    func(const char *infix) {
        stack<int> stck;
        stck.push(OPEN);
        bool expectNeg = 1;
        for (int i = 0; !i || infix[i - 1]; ++i) {
            if (infix[i] == 'x') {
                postfix.push_back(X);
                expectNeg = 0;
            } else if (infix[i] == '.' || isdigit(infix[i])) {
                double num;
                sscanf(infix + i, "%lf", &num);
                while (infix[i] == '.' || isdigit(infix[i]))
                    ++i;
                --i;
                postfix.push_back(constants.size());
                constants.push_back(num);
                expectNeg = 0;
            } else if (infix[i] == '(') {
                stck.push(OPEN);
                expectNeg = 1;
            }else if (!infix[i] || infix[i] == ')') {
                while (1) {
                    int popped = stck.top();
                    stck.pop();
                    if (popped == OPEN) break;
                    postfix.push_back(popped);
                }
                expectNeg = 0;
            } else {
                int op = infix[i] == '*' ? MUL : infix[i] == '/' ? DIV : infix[i] == '-' ? MINUS : PLUS;
                while (op / 2 <= stck.top() / 2) {
                    postfix.push_back(stck.top());
                    stck.pop();
                }
                if(expectNeg && op == MINUS)
                    postfix.push_back(0);

                stck.push(op);
                expectNeg = 1;
            }
        }
    }

    double operator()(double x) {
        stack<double> stck;
        constants[0] = x;
        for (int v : postfix) {
            if (v >= 0)
                stck.push(constants[v]);
            else {
                double b = stck.top(), a = (stck.pop(), stck.top()), ans;
                stck.pop();
                if (v == PLUS)
                    ans = a + b;
                else if (v == MINUS)
                    ans = a - b;
                else if (v == MUL)
                    ans = a * b;
                else
                    ans = a / b;
                stck.push(ans);
            }
        }
        return stck.top();
    }
};