#include "std_lib_facilities.h"
#include "custom_token.h"


const string prompt = "> ";
const string result = "= ";



vector<Variable> var_table;

double get_value(string s)
{
    for (int i = 0; i<var_table.size(); ++i)
        if (var_table[i].name == s) return var_table[i].value;
    error("get: undefined variable ", s);
}

void set_value(string s, double d)
{
    for(Variable& var : var_table)
        if(var.name == s) {
            var.value = d;
            return;
        }
    var_table.push_back(Variable{s, d});
}


double statement(Token_stream& ts);
double expression(Token_stream& ts);
double term(Token_stream& ts);
double primary(Token_stream& ts);
double expon(Token_stream& ts);


double statement(Token_stream& ts){
    Token t = ts.get();
    if (t.kind == name){
        Token variable = t;
        t = ts.get();
        if (t.kind == '='){
            double d = expression(ts);
            set_value(variable.name, d);
            return d;
            }
        else if(t.kind == print){
            ts.putback(t);
            return get_value(variable.name);
        }
        ts.putback(t);
        ts.putback(variable);
        return expression(ts);
    }
    ts.putback(t);
    return expression(ts);
}



double expression(Token_stream& ts){
    double left = term(ts);
    Token t = ts.get();

    while(true){
        switch(t.kind){
        case '+':
            left += term(ts);
                    t = ts.get();

            break;
        case '-':
            left -= term(ts);
                    t = ts.get();

            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

double term(Token_stream& ts){

    double left = expon(ts);
    Token t = ts.get();

    while(true) {
        switch (t.kind) {
            case '*':
            {
                left *= expon(ts);
                t = ts.get();
                break;
            }
            case '/':
            {
                double term = expon(ts);
                if (term == 0)
                    error("divide by zero");
                left /= term;
                t = ts.get();
                break;
            }
            case '%':
            {
                double d = expon(ts);
                if (d == 0)
                    error("divide by zero");
                left = fmod(left, d);
                t = ts.get();
                break;
            }
            default:
            {
                ts.putback(t);
                return left;
            }
        }
    }
}

double expon(Token_stream& ts)
{
/* grammar recognized:
Exp:
    Primary
    Primary "^" Primary
*/
    double left = primary(ts);
    Token t = ts.get();
    if(t.kind == power) {
        double d = primary(ts);
        return pow(left, d);
    }
    else {
        ts.putback(t);     // put t back into the token stream
        return left;
    }
}

double primary(Token_stream& ts){
	Token t = ts.get();
    switch (t.kind) {
    case '(':{
        double d = expression(ts);
        t = ts.get();
        if (t.kind != ')') error("closing parentheses expected");
        return d;
        }
    case number:
        return t.value;
    case '-':
        return -primary(ts);
    case '+':
        return primary(ts);
    case name:
        return get_value(t.name);
    default:
        string s(1, t.kind);
        error("primary expected; got " + s);
    }
}

//int main(){
//    Token t = ts.get();
//    while(t.kind != 'q'){
//        cout << "kind " << t.kind << " and value " << t.value << "\n";
//        t = ts.get();
//    }
//}

void print_token(Token t){
cout << "token: " << t.kind
        << " with val of " << t.value << '\n';
}

void clean_up_mess(Token_stream& ts)
{
    ts.ignore(print);
}

void calculate(Token_stream& ts)
{
    while(cin) {
        try {
            cout << prompt;
            Token t = ts.get();
// this output is for debugging:
//			cout << "in main(), got token: " << t.kind
//				<< " with val of " << t.value << '\n';
            while(t.kind == print) t = ts.get();
            if(t.kind == quit) return;
            ts.putback(t);
            cout << result << setprecision(8) << statement(ts) << '\n';
        }
        catch(exception& e) {
            cerr << e.what() << '\n';
            clean_up_mess(ts);
        }
    }

}


void load(){
    string save;
    cin >> save;
    ifstream var_list {save};
    if (save == "N/A") return;
    if (!var_list){
    cout << "Saved session not found, please re-enter:\n";
    load();
    }
    string name;
    int value;
    while (var_list >> name >> value){
    set_value(name, value);
    }
}

void intro(){
    cout << "Welcome to my C++ calculator\n"
        << "It can handle operations +, -, *, /, %, and ^\n"
        << "Enter ; in order to print out the result "
        << "and q in order to quit the program\n"
        << "Set a variable by inputting 'variable name = value'\n"
        << "As an added feature, this calculator also support saving and restoring variables from previous sessions\n"
        << "Feel free to use the attached 'vars' test file in order to test the variables\n"
        << "Or save a new log file at the end of this session and load it in the next run\n";
    cout << "Enter the name of a saved variable session\n"
            << "If no session is available, enter N/A:\n";
    return;
}


void save(){
    string log;
    cout << "Please enter name of output file: \n";
    cin >> log;
    ofstream out_log {log};
    if (!out_log) error("can't open output file ", log);
    for(Variable curr : var_table){
        out_log << curr.name << " " << curr.value << '\n';
    }
    cout << "File successfully saved in " << log << '\n';
    return;
}

int main(){
    try{
        intro();
        Token_stream ts;
        load();
        calculate(ts);
        save();
        return 0;
    }
    catch (exception& e) {
        cerr << e.what() << endl;
        keep_window_open("~~");
        return 1;
    }
    catch (...) {
        cerr << "exception \n";
        keep_window_open("~~");
        return 2;
    }
}
