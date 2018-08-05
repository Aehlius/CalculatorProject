#include "std_lib_facilities.h"
#include "token.h"

vector <Token> tokens;

Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}


void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;
    full = true;
}


Token Token_stream::get(){
    if (full){
        full = false;
        return buffer;
    }
    char ch;
	cin >> ch;
	switch(ch){
    	case print:
    	case quit:
        case '(':
        case ')':
        case '+':
        case '-':
        case '/':
        case '*':
        case '%':
        case power:
    		return Token{ch};
    	case '.':
    	case '0':
    	case '1':
    	case '2':
    	case '3':
    	case '4':
    	case '5':
    	case '6':
    	case '7':
    	case '8':
    	case '9':
    		cin.putback(ch);
    		double val;
    		cin >> val;
    		return Token{number, val};
        default:
            if(isalpha(ch)) {
                string s;
                s += ch;
                while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                cin.putback(ch);
                return Token{name, s};
            }
            return Token{invalid, double(ch)};
    }
    return Token{quit};
}


void Token_stream::ignore(char c)
    // c is token kind to look for
{
    // first check buffer:
    if(full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // now search input:
    char ch = 0;
    while(cin >> ch)
        if(ch == c) return;
}
