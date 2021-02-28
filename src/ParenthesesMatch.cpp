#include "../inc/ParenthesesMatch.h"
#include "../inc/Stack.h"

/**
 * @brief Determines whether or not all the parenthesis in a string match. Meaning for every '(' there is
 *       another ')'.
 * @param str - String that you want to search for corresponding parenthesis.
 * @return bool - true: If there are no parenthesis or if every open parenthesis has a closing parenthesis.
 *               false: If the parenthesis do not match.
 */
bool parenthesesMatch(const char* str) {
    Stack<char> stack;
    int index = 0;
    while (str[index] != '\0') {
        if (str[index] == '(') {
            stack.push('*');
        }
        if (str[index] == ')') {
            if (stack.empty()) {
                return false;
            }
            stack.pop();
        }

        index++;
    }
    if (stack.empty()) {
        return true;
    }
    return false;
}