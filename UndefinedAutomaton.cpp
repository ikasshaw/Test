#include "UndefinedAutomaton.h"

void UndefinedAutomaton::S0(const std::string& input) {
    
    if (input[index] == '#' ) {
        ++inputRead;
        ++index;
        S1(input);
        
    }
    
    else if (input[index] == '\'' ) {
        
        index++;
        ++inputRead;
        if (input[index] =='\'') {
            Serr();
        }
        else {
        S2(input);
        }

    }
    else {
        Serr();
    }
}

void UndefinedAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        
        inputRead = static_cast<int>(input.size());
        index++;
        
        if (Search(input, '|')) {
            Serr();
        }
        else {            
            return;
        }
    }
    else {
        Serr();
    }
}

void UndefinedAutomaton::S2(const std::string& input) {
    if (index == static_cast<int>(input.size() - 1)) {
        inputRead = static_cast<int>(input.size());
        if (input[index] == '\n') {
            ++newLines;
            }
        return;
    }
    else if (isspace(input[index])) {
        if (input[index] == '\n') {
            ++newLines;
        }
        ++index;
        S2(input);
    }
    else if (input[index] == '\'' && input[index + 1] != '\'' && input[index - 1] != '\'') {
        if (input[index] == '\n') {
            ++newLines;
            }
        return;
    }
    
    else if (input[index] == '\'' && input[index + 1] == '\'') {
        ++index;
        S2(input);
    }
    else if (input[index] == '\'' && input[index - 1] == '\'') {
        ++index;
        S2(input);
    }
    
    else if (input[index] != '\'') {
        if (input[index] == '\n') {
            ++newLines;
            }
            
        ++index;
        S2(input);
    }
    else {
        Serr();
    }
}

bool UndefinedAutomaton::Search(const string& input, char c) {
    
    char checker;
    for (int i = 0; i < inputRead; ++i) {
        checker = input[i];
        
        if (checker == '\n') {
            ++newLines;
        }
        
        else if (checker == c) {
            if (c == '|') {
                if (i < (inputRead - 1) && input[i + 1] == '#') {
                    return true;
                }
            }
        }
    }
return false;
}