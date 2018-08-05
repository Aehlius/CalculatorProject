const char invalid = 'i';
const char name = 'a';
const char number = '8';
const char quit = 'q';
const char print = ';';
const char power = '^';



class Token{
    public:
        char kind;      //if it's 8, double has a value
        double value;
        string name;
        Token(char ch) :kind{ch} {}
        Token(char ch, double val) :kind{ch}, value{val} {}
        Token(char ch, string n) :kind{ch}, name{n} {}
    };



class Token_stream{
    public:
        Token_stream();
        Token get();
        void putback(Token t);
        void ignore(char c);
    private:
        Token buffer{invalid};
        bool full{false};
    };


class Variable {
    public:
        string name;
        double value;
};

double get_value(string s);
void set_value(string s, double d);