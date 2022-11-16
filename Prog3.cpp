#include <iomanip>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

bool isReserved(string subCode) {
    char reservedWords[4][10]={ "cout<<", "for", "int", "while"};
    for (int i = 0; i < 4; ++i) {
        if (subCode == reservedWords[i]) {
            return true;
        }
    }
    return false;
}

bool isOperator(string subCode) {
    char oper[6][3]={ "+", "-", "*", "/", "++", "--"};
    for (int i = 0; i < 6; ++i) {
        if (subCode == oper[i]) {
            return true;
        }
    }
    return false;
}

bool isSpecial(string subCode) {
    char special[7][3]={"<", "=" , ";" , "(" , ")" , "<=" ,","};
    for (int i = 0; i < 7; ++i) {
        if (subCode == special[i]) {
            return true;
        }
    }
    return false;
}

bool isNumber(string subCode) {
    string::size_type textPortion;
    try {
        int numTest = stoi(subCode, &textPortion);
    }
    catch(invalid_argument) {
        return false;
    }

    if (subCode.substr(textPortion) == "") {
        return true;
    }
    else {
        return false;
    }
}

bool isIdentifier(string subCode) {
    string::size_type textPortion;
    try {
        int numTest = stoi(subCode, &textPortion);
    }
    catch(invalid_argument) {
        return true;
    }
    return false;
}

int main() {
    string codeLine;
    string cont = "y";

    while (cont == "y" || cont == "Y") {
    cout << "Enter a statement: \n";
    getline(cin, codeLine);
    cout << "\n";

    int currSpace = 0;
    int prevSpace;
    int extraSpace = 0;
    int addSpace = 0;

    for (int i = 0; i < codeLine.length(); ++i) {
        string subCode;

        if (codeLine[i] == ' ' || i == codeLine.length() - 1) {
            //cout << "DEBUG \n";
            if (codeLine[i+1] == ' ') {
                extraSpace++;
                continue;
            }
            else {
                prevSpace = currSpace + addSpace;
                currSpace = i - extraSpace;
                addSpace = extraSpace;
                extraSpace = 0;
            }

            if (prevSpace == 0) {
                subCode = codeLine.substr(0, currSpace);
            }
            else if (i == codeLine.length() - 1) {
                subCode = codeLine.substr(currSpace, string::npos);
            }
            else {
                subCode = codeLine.substr(prevSpace + 1, currSpace - prevSpace - 1);
            }

            std::transform(subCode.begin(), subCode.end(), subCode.begin(), ::tolower);

            if (isReserved(subCode)) {
                cout << subCode << setw(50) <<"Reserved Word\n";
            }
            else if (isOperator(subCode)) {
                cout << subCode << setw(50) << "Operator\n";
            }
            else if (isSpecial(subCode)) {
                cout << subCode << setw(50) << "Special Symbol\n";
            }
            else if (isNumber(subCode)) {
                cout << subCode << setw(50) << "Number\n";
            }
            else if (isIdentifier(subCode)) {
                cout << subCode << setw(50) << "Identifier\n";
            }
            else {
                cout << subCode << setw(50) << "Not Identifier\n";
            }
        }
        
    }
    cout << "\n" << "CONTINUE(y/n)? ";
    cin >> cont;
    cin.ignore();
    cout << "\n";
    }

}