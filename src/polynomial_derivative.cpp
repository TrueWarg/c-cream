#include <iostream>
#include <map>
#include <regex>

using namespace std;

int sign_of(const char &ch)
{
    if (ch == '-')
        return -1;
    return 1;
}

map<int, int, greater<int>> parse_polynomial(const string &polynomial)
{
    map<int, int, greater<int>> degrees_to_coeffs;

    const regex polynomial_regex("([+-]?[^-+]+)");

    regex_token_iterator<string::const_iterator> end;
    // token is {sign k * x^a}
    regex_token_iterator<string::const_iterator> tokens(
        polynomial.begin(),
        polynomial.end(),
        polynomial_regex);

    while (tokens != end)
    {
        int degree;
        int coefficient;
        const string token = *tokens++;

        int separator_index = token.find('x');

        // no need to append free coefficient, they will be null after derivative operation
        if (separator_index == string::npos)
            continue;

        if (separator_index == token.length() - 1)
            degree = 1;
        else
            // +2 for ^ handling
            degree = strtol(token.substr(separator_index + 2).c_str(), NULL, 10);

        // for x^0 case (free coefficient, see above)
        if (degree == 0)
            continue;

        // cases: x, -x, +x
        if (separator_index == 0 || separator_index == 1)
            coefficient = sign_of(token[0]);
        else
            coefficient = strtol(token.c_str(), NULL, 10);

        degrees_to_coeffs[degree] += coefficient;
    }

    return degrees_to_coeffs;
}

string create_formatted_derivative(const map<int, int, greater<int>> &polynomial)
{
    string out = "";

    for (
        auto iterator = polynomial.begin();
        iterator != polynomial.end();
        iterator++)
    {
        const int degree = iterator->first;
        const int coeff = iterator->second;
		const string sign = iterator == polynomial.begin() || coeff < 0 ? "" : "+";

        if (degree == 1)
        {
            out += sign + to_string(coeff);
        } else {
            const string formatted_degree = degree > 2 ? '^' + to_string(degree - 1) : ""; 
            out += sign + to_string(coeff * degree) + "*x" + formatted_degree;
        }
    }

    return out;
}

string derivative(string polynomial)
{
    map<int, int, greater<int>> degrees_to_coeffs = parse_polynomial(polynomial);
    return create_formatted_derivative(degrees_to_coeffs);
}
