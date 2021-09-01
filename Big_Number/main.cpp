//#include <iostream>
#include"Integer.h"
#include"Float.h"
//#include"precedence.h"
#include<string>
#include<vector>
#include <map>
//#include <string_view>
#include<sstream>
#include<iterator>
#include<cmath>
//#define DEBUG
using namespace std;

void inToPostfix(string&, string&);
int priority(char);
void convert(string& postfix, int pos);
//void convert_fac(string& postfix, int pos);
double calculate(string& postfix);
void Init(string& inp);
void Reset();

#ifdef DEBUG
map<string, int>minisint{ {"tempa",0} ,{"tempb",0} ,{"temph",0} ,{"tempf",0} };   //full scope variable integer float
map<string, double>minisflo{ {"tempa",0} ,{"tempb",0} ,{"temph",0} ,{"tempf",0} };   //full scope variable integer float
map<string, int>::iterator iteri;
map<string, double>::iterator iterf;
#endif // DEBUG
#ifndef DEBUG
Int ZeroI;
Float ZeroF;
map<string, Int>minisint{ {"tempa",ZeroI} ,{"tempb",ZeroI} ,{"temph",ZeroI},{"tempf",ZeroI} };   //full scope variable integer float
map<string, Float>minisflo{ {"tempa",ZeroF} ,{"tempb",ZeroF} ,{"temph",ZeroF},{"tempf",ZeroF} };   //full scope variable integer float
map<string, Int>::iterator iteri;
map<string, Float>::iterator iterf;
#endif // !DEBUG
int counter_string = 0;

void Reset() {
    minisint["tempa"] = 0;
    minisflo["tempa"] = 0;
    minisint["tempb"] = 0;
    minisflo["tempb"] = 0;
    minisint["temph"] = 0;
    minisflo["temph"] = 0;
}

void ResetA() {
    for (int i = 1; i < counter_string; i++) {
        stringstream ss;
        ss << "tmp" << i;
        string temp;
        ss >> temp;
        minisint.erase(temp);
        minisflo.erase(temp);
    }
}


void  printA() {
    cout << "minisint[\"tempa\"]" << minisint["tempa"] << endl;
    cout << "minisflo[\"tempa\"]" << minisflo["tempa"] << endl;
    cout << "minisint[\"tempb\"]" << minisint["tempb"] << endl;
    cout << "minisflo[\"tempb\"]" << minisflo["tempb"] << endl;
    cout << "minisint[\"temph\"]" << minisint["temph"] << endl;
    cout << "minisflo[\"temph\"]" << minisflo["temph"] << endl;
}

string convert_string_nums() {
    counter_string++;
    stringstream ss;
    ss << "tmp";
    ss << counter_string;
    string converted;
    ss >> converted;
    return converted;
}

int main()
{
#ifdef DEBUG
    cout << "DEBUG MODE DEF No big number was entered" << endl;
#endif // DEBUG
    string infix;
    string postfix;
    cout << "Line: ";

    while (getline(cin, infix)) {
        //printA();
        //check if it is no print out function
        bool ifprt = true;
        //bool cal = false;
        for (auto i : infix) {
            if (i == '=') {
                ifprt = false;
            }
        }
        if (ifprt) {
            //for check if it is assigned
            stringstream sst;
            sst << infix;
            string tmp;
            sst >> tmp;
            if (tmp == "set") {
                cout << "please assign value you are very smart." << endl;
                cout << "Line: ";
                continue;
            }
            infix.push_back('+');
            infix.push_back('0');
            inToPostfix(infix, postfix);
            calculate(postfix);
            postfix.erase(postfix.begin());
            postfix.erase(postfix.end() - 1);
            if (!(minisint[postfix] == 0)) {
                cout << "Resault is: " << minisint[postfix] << endl;
            }
            else if (!(minisflo[postfix] == 0)) {
                cout << "Resault is: " << minisflo[postfix] << endl;
            }
            else {
                cout << "Resault is: " << 0 << endl;
            }
        }
        else {
            //set or cal only
            Init(infix);
        }
        infix.clear();
        postfix.clear();
        ResetA();
        counter_string = 0;
        //printA();
        cout << "Line: ";
    }

    return 0;
}

void Init(string& inp) {

    stringstream ss;
    ss << inp;
    string t1;
    ss >> t1;
    if (t1 == "set") {
        string t2;
        ss >> t2;
        string t3;
        ss >> t3;   //variable name

        string equ; //= =   //set int A = 1 * 3 * 4 * 5
        ss >> equ;  //for god sake just don't read this sign
        string tempt;

        string postfix;
        getline(ss, tempt);
        string infix = tempt;
        infix.push_back('+');
        infix.push_back('0');
        inToPostfix(infix, postfix);
        calculate(postfix);

        postfix.erase(postfix.begin());
        postfix.erase(postfix.end() - 1);
        //cout << "postfix is: " << postfix << endl;
        if (t2 == "int") {
#ifdef DEBUG
            //string to num
            stringstream sstest;
            sstest << postfix;
            sstest >> minisint[t3]; //minisint[t3] = postfix;
#endif // DEBUG
#ifndef DEBUG  
             if (!(minisint[postfix] == 0)){
                 stringstream ss;
                 ss << minisint[postfix];
                 minisint[t3] = ss.str();
             }
             else if (!(minisflo[postfix] == 0)) {
                 stringstream ss;
                 ss << minisflo[postfix];
                 minisint[t3] = ss.str();
                 //minisint[t3] = minisflo[postfix].top / minisflo[postfix].bottom;
            }
             else{
                 minisint[t3] = 0;
             }
            //minisint[t3] = Int(postfix); //minisint[t3] = postfix;
            //minisint[t3] = postfix;
#endif
        }
        else if (t2 == "dec") {
#ifdef DEBUG
            //string to num
            stringstream sstest;
            sstest << postfix;
            sstest >> minisflo[t3];
#endif // DEBUG
#ifndef DEBUG
           if (!(minisint[postfix] == 0)) {
                stringstream ss;
                 ss << minisint[postfix];
                 minisflo[t3] = ss.str();
                //minisflo[t3] = minisint[postfix];
            }
            else if (!(minisflo[postfix] == 0)) {
                 stringstream ss;
                 ss << minisflo[postfix];
                 minisflo[t3] = ss.str();
            }
            else {
                minisflo[t3] = 0;
            }
            //minisflo[t3] = postfix;
#endif
        }
    }
    else {  //normal equility set again function ex. A = A //t1 = A

        string equ; //= =
        ss >> equ;  //for just don't read this sign
        string tempt;

        string postfix;
        getline(ss, tempt);
        string infix = tempt;       //let B = A become B = A + 0
        infix.push_back('+');
        infix.push_back('0');       //A = A * 0.5
        inToPostfix(infix, postfix);
        calculate(postfix);
        postfix.erase(postfix.begin());
        postfix.erase(postfix.end() - 1);
        //cout << minisint[postfix] << endl;
        //cout << minisflo[postfix] << endl;
        iteri = minisint.find(t1);
        iterf = minisflo.find(t1);
        if (iteri != minisint.end()) {          //minisint[t1] is available
            if (!(minisint[postfix] == 0)) {
                minisint[t1] = minisint[postfix];
            }
            else if(!(minisflo[postfix] == 0)) {
                minisint[t1] = minisflo[postfix].top / minisflo[postfix].bottom;
            }
            else {
                minisint[t1] = 0;
            }
        }
        else if (iterf != minisflo.end()) {      //minisflo[t1] is available
            if (!(minisint[postfix] == 0)) {
                minisflo[t1] = minisint[postfix];
            }
            else if (!(minisflo[postfix] == 0)) {
                minisflo[t1] = minisflo[postfix];
            }
            else {
                minisflo[t1] = 0;
            }
        }
        else {
            cout << "Didn't find variable '"<< t1 <<"' . Please define it." << endl;
        }
        //cout << minisint[t1] << endl;
        //cout << minisflo[t1] << endl;
    }

    ss.clear();
}

void convert_fac(string& postfix, int pos) {
    //cout << postfix << endl;
    string a;
    //for declare map s
    string tempa = "tempa";
    string temph = "temph";
    stringstream sstest;
    string tempf = convert_string_nums();
    int i = pos;
    while (postfix[i] != ';') {
        a.push_back(postfix[i]);
        postfix.erase(postfix.begin() + i);
    }
    postfix.erase(postfix.begin() + i);
    //become ;a;!;

    iterf = minisflo.find(a);
    iteri = minisint.find(a);
    if (iterf != minisflo.end()) {
        if (minisflo[a].bottom == 1) {
            minisflo[tempf] = minisflo[a].Fac();
            minisint.erase(tempf);
            //cout << "Flo Before insert. "<< postfix << endl;
            postfix.erase(postfix.begin() + pos);
            postfix.insert(pos, tempf);
            //cout << "After insert. " << postfix << endl;
            return;
        }
        else {
            postfix.erase(postfix.begin() + 1, postfix.end() - 1);
            postfix.insert(1, "Error.");
            cout << "Your float can't be factorial" << endl;
            return;
        }

    }
    else if (iteri != minisint.end()) {
        if (!(minisint[a] >= 0)) {
            postfix.erase(postfix.begin() + 1, postfix.end() - 1);
            postfix.insert(1, "Error.");
            cout << "it can't be negetive numbers." << endl;
            return;
        }
        else {
            minisint[tempf] = minisint[a].Fac();
            minisflo.erase(tempf);
            //cout << "Int Before insert. " << postfix << endl;
            postfix.erase(postfix.begin() + pos);
            postfix.insert(pos, tempf);
            //cout << "After insert. " << postfix << endl;
            return;
        }
    }
    else {       //normal number
        //bottom
        int callt = 0;
        for (auto t : a) {
            if (t == '.') {
                callt = 1;
            }
        }
        if (callt == 1) {
            //minimap[tempa] = Float(a);
            sstest << a;
            double fff;
            sstest >> fff;
            minisflo[tempa] = fff;
            minisint[tempa] = 0;
            sstest.clear();
        }
        else {
            //minimap[tempa] = Int(a);
            sstest << a;
            int ddd;
            sstest >> ddd;
            minisint[tempa] = ddd;
            minisflo[tempa] = 0;
            sstest.clear();
            //Int tempa
        }
        stringstream ss;
        ss << a;
        ss >> minisint[tempa];
        if (!(minisint[tempa] >= 0)) {
            postfix.erase(postfix.begin() + 1, postfix.end() - 1);
            postfix.insert(1, "Error.");
            cout << "it can't be negetive numbers." << endl;
            minisint[tempa] = 0;
            return;//hah
        }
        else if(!(minisflo[tempa].bottom == 1)){
            postfix.erase(postfix.begin() + 1, postfix.end() - 1);
            postfix.insert(1, "Error.");
            cout << "Your float can't be factorial." << endl;
            minisflo[tempa] = 0;
            return;
        }
        else {
            minisint[tempf] = minisint[tempa].Fac();
            minisflo.erase(tempf);
            //cout << "normal Num Before insert. " << postfix << endl;
            postfix.erase(postfix.begin() + pos);
            postfix.insert(pos, tempf);
            //cout << "After insert. " << postfix << endl;
            return;
        }
    }
}

void convert(string& postfix, int pos) {    
    //pos means first arawareta no ; ato 1 go
    //cout << postfix << endl;
    //cout << postfix << endl;
    string a, b;
    //for declare map s
    string tempa = "tempa";
    string tempb = "tempb";
    string temph = "temph";
    stringstream sstest;
    int callt = 0;

    //cout << "position is" << pos << endl;
    int i = pos;

    while (postfix[i] != ';') {
        a.push_back(postfix[i]);
        postfix.erase(postfix.begin() + i);
    }
    postfix.erase(postfix.begin() + i);
    //printA();
    //cout << a << endl;
    iteri = minisint.find(a);
    iterf = minisflo.find(a);
    if (iteri != minisint.end()) {
        //cout << "find tempA Int value is" << iteri->second << endl;
        minisint[tempa] = minisint[a];
        //minisflo[tempa] = 0;
    }
    else if (iterf != minisflo.end()) {
        //cout << "find tempA Float value is" << iterf->second << endl;
        minisflo[tempa] = minisflo[a];
        //minisint[tempa] = 0;
    }
    else {
        callt = 0;
        for (auto t : a) {
            if (t == '.') {
                callt = 1;
            }
        }
        if (callt == 1) {
            //minimap[tempa] = Float(a);
            sstest << a;
            double fff;
            sstest >> fff;
            minisflo[tempa] = fff;
            minisint[tempa] = 0;
            sstest.clear();
        }
        else {
            //minimap[tempa] = Int(a);
            sstest << a;
            int ddd;
            sstest >> ddd;
            minisint[tempa] = ddd;
            minisflo[tempa] = 0;
            sstest.clear();
            //Int tempa
        }
    }
    //printA();
    while (postfix[i] != ';') {
        b.push_back(postfix[i]);
        postfix.erase(postfix.begin() + i);
    }
    postfix.erase(postfix.begin() + i);
    //become like this type ;a;b;operator;

    iteri = minisint.find(b);
    iterf = minisflo.find(b);
    if (iteri != minisint.end()) {
        //cout << "find tempB Int value is" << iteri->second << endl;
        minisint[tempb] = minisint[b];
    }
    else if (iterf != minisflo.end()) {
        //cout << "find tempB Float value is" << iterf->second << endl;
        minisflo[tempb] = minisflo[b];
    }
    else {
        callt = 0;
        for (auto t : b) {
            if (t == '.') {
                callt = 1;
            }
        }
        if (callt == 1) {
            //minimap[tempb] = Float(b);
            sstest << b;
            double fff;
            sstest >> fff;
            minisflo[tempb] = fff;
            minisint[tempb] = 0;
            sstest.clear();
            //Float tempb   //temp b
        }
        else {
            //minimap[tempb] = Int(b);
            sstest << b;
            int ddd;
            sstest >> ddd;
            minisint[tempb] = ddd;
            minisflo[tempb] = 0;
            sstest.clear();
            //Int tempb
        }
    }
    //printA();
    switch (postfix[i]) {
    case '+': //+ tempa + tempb
        //version 3
        //minimap[temph] = minimap[tempa] + minimap[tempb];
        if (minisflo[tempa] == 0 && minisflo[tempb] == 0) {         //both are integer
            minisint[temph] = minisint[tempa] + minisint[tempb];
        }
        else if (minisint[tempa] == 0 && minisflo[tempb] == 0) {    //tempa is float
            minisflo[temph] = minisflo[tempa] + minisint[tempb];
        }
        else if (minisflo[tempa] == 0 && minisint[tempb] == 0) {    //tempb is float
            minisflo[temph] = minisint[tempa] + minisflo[tempb];
        }
        else if (minisint[tempa] == 0 && minisint[tempb] == 0) {    //both are float
            minisflo[temph] = minisflo[tempa] + minisflo[tempb];
        }

        break;
    case '-': //-   //tempa - tempb
        //minimap[temph] = minimap[tempa] - minimap[tempb];
        if (minisflo[tempa] == 0 && minisflo[tempb] == 0) {         //both are integer
            minisint[temph] = minisint[tempa] - minisint[tempb];
        }
        else if (minisint[tempa] == 0 && minisflo[tempb] == 0) {    //tempa is float
            minisflo[temph] = minisflo[tempa] - minisint[tempb];
        }
        else if (minisflo[tempa] == 0 && minisint[tempb] == 0) {    //tempb is float
            minisflo[temph] = minisint[tempa] - minisflo[tempb];
        }
        else if (minisint[tempa] == 0 && minisint[tempb] == 0) {    //both are float
            minisflo[temph] = minisflo[tempa] - minisflo[tempb];
        }

        break;
    case '*': //* tempa * tempb
        //minimap[temph] = minimap[tempa] * minimap[tempb];
        if (minisint[tempa] == 0 && minisint[tempb] == 0) {         //both are float
            minisflo[temph] = minisflo[tempa] * minisflo[tempb];
        }
        else if (minisint[tempa] == 0 && minisflo[tempb] == 0) {    //tempa is float
            minisflo[temph] = minisflo[tempa] * minisint[tempb];
        }
        else if (minisflo[tempa] == 0 && minisint[tempb] == 0) {    //tempb is float
            minisflo[temph] = minisint[tempa] * minisflo[tempb];
        }
        else if (minisflo[tempa] == 0 && minisflo[tempb] == 0) {    //both are integer
            minisint[temph] = minisint[tempa] * minisint[tempb];
        }
        break;
    case '/': //div     //1 / 3.0 * 3 -> 1 3.0 / 3 * -> temph * 3    -> temph = 1
                        //1 / 3.0 * 3 -> 1 3.0 / 3 * -> 0.33333 3 *  -> 0.99999
        //minimap[temph] = minimap[tempa] / minimap[tempb];
        if (minisint[tempb] == 0 && minisflo[tempb] == 0) {
            postfix.erase(postfix.begin() + 1, postfix.end() - 1);
            postfix.insert(1, "Error.");
            cout << "Can't devided by zero." << endl;
            return;
        }
        if (minisint[tempa] == 0 && minisint[tempb] == 0) {         //both are float
            minisflo[temph] = minisflo[tempa] / minisflo[tempb];
        }
        else if (minisint[tempa] == 0 && minisflo[tempb] == 0) {    //tempa is float
            minisflo[temph] = minisflo[tempa] / minisint[tempb];
        }
        else if (minisflo[tempa] == 0 && minisint[tempb] == 0) {    //tempb is float
            minisflo[temph] = minisint[tempa] / minisflo[tempb];
        }
        else if (minisflo[tempa] == 0 && minisflo[tempb] == 0) {    //both are integer
            minisint[temph] = minisint[tempa] / minisint[tempb];
        }
        break;
    case '^':
#ifdef DEBUG
        //printA();
        if (minisint[tempa] == 0 && minisint[tempb] == 0) {         //both are float
            minisflo[temph] = pow(minisflo[tempa], minisflo[tempb]);
        }
        else if (minisint[tempa] == 0 && minisflo[tempb] == 0) {    //tempa is float
            minisflo[temph] = pow(minisflo[tempa], minisint[tempb]);
        }
        else if (minisflo[tempa] == 0 && minisint[tempb] == 0) {    //tempb is float
            minisflo[temph] = pow(minisint[tempa], minisflo[tempb]);
        }
        else if (minisflo[tempa] == 0 && minisflo[tempb] == 0) {    //both are integer
            minisint[temph] = int(pow(minisint[tempa], minisint[tempb]));
        }
#endif // DEBUG
#ifndef DEBUG
        if (minisint[tempa] == 0 && minisint[tempb] == 0) {         //both are float
             if(!(minisflo[tempb].bottom==2)){
                cout << "Wrong input" << endl;
                postfix.clear();
                postfix.insert(0,";;");
                return;
            }
            minisflo[temph] = minisflo[tempa] ^ minisflo[tempb];
        }
        else if (minisint[tempa] == 0 && minisflo[tempb] == 0) {    //tempa is float
            minisflo[temph] = minisflo[tempa] ^ minisint[tempb];
        }
        else if (minisflo[tempa] == 0 && minisint[tempb] == 0) {    //tempb is float
            if(!(minisflo[tempb].bottom==2)){
                cout << "Wrong input" << endl;
                postfix.clear();
                postfix.insert(0,";;");
                return;
            }
            minisflo[temph] = minisint[tempa] ^ minisflo[tempb];
        }
        else if (minisflo[tempa] == 0 && minisflo[tempb] == 0) {    //both are integer
            minisint[temph] = minisint[tempa] ^ minisint[tempb];
        }
#endif // !DEBUG
        break;
    }
    string tempf = convert_string_nums();
    //cout << "before assign: " << minisint[temph] << "\nbefore assign: " << minisflo[temph] << endl;
    if (minisflo[temph] == 0) { //integer insert    //class name insert
        minisint[tempf] = minisint[temph];
        minisflo.erase(tempf);
    }
    else if (minisint[temph] == 0) {
        minisflo[tempf] = minisflo[temph];
        minisint.erase(tempf);
    }
    Reset();
    postfix.erase(postfix.begin() + pos);
    postfix.insert(pos, tempf);
    //cout << "After insert: " << postfix << endl;
    return;
    //postfix.insert(pos,temp);
}

double calculate(string& postfix) {
    int counter = 0;

    for (size_t i = 0; i < postfix.size(); i++) {
        counter = 0;
        int j;
        switch (postfix[i]) {
        case '!':
            for (j = i; counter < 2; j--) {
                if (postfix[j] == ';') {
                    counter++;
                }
            }
            i = 0;
            convert_fac(postfix, j + 2);
            break;
        case '+':case '-':case '*':case '/':case '^':
            j = i;
            if (postfix[j + 1] != ';') {
                break;
            }
            for (; counter < 3; j--) {
                if (postfix[j] == ';') {
                    counter++;
                }
            }
            i = 0;
            convert(postfix, j + 2);
            break;
        default:
            break;
        }
    }
    return 0;
}

void inToPostfix(string& infix, string& postfix) {
    for (size_t i = 0; i < infix.size(); i++) {
        if (infix[i] == ' ') {
            infix.erase(infix.begin() + i);
        }
    }
    char stack[300]{ '\0' };
    int i, j, top;
    postfix.push_back(';');
    infix.push_back(';');
    for (i = 0, j = 0, top = 0; infix[i] != '\0'; i++) {
        //cout << "Infix is " << infix << endl;
        //cout << "Postfix is " << postfix << endl;
        switch (infix[i]) {
        case '(':              // operator stack 
            stack[++top] = infix[i];
            break;
        case '+': case '-':
            //if (i != 0) {
            if (i == 0) {
                postfix.push_back('0');
                postfix.push_back(';');
                stack[++top] = infix[i];
            }
            else if (infix[i - 1] == '('
                || infix[i - 1] == '-'
                || infix[i - 1] == '+'
                || infix[i - 1] == '*'
                || infix[i - 1] == '/') {
                postfix.push_back('0');
                postfix.push_back(';');
                stack[++top] = infix[i];
            }
            else {
                postfix.push_back(';');
                while (priority(stack[top]) >= priority(infix[i])) {
                    postfix.push_back(stack[top--]);
                    postfix.push_back(';');
                }
                stack[++top] = infix[i]; // in stack
            }
            //huh            
            break;
        case '!':
            //postfix.push_back(';');
            while (priority(stack[top]) >= priority(infix[i])) {
                postfix.push_back(';');
                postfix.push_back(stack[top--]);
            }
            stack[++top] = infix[i]; // in stack//
            break;
        case '^':
            postfix.push_back(';');
            while (priority(stack[top]) > priority(infix[i])) {
                postfix.push_back(';');
                postfix.push_back(stack[top--]);
            }
            stack[++top] = infix[i]; // in stack//
            break;
        case '*': case '/':
            postfix.push_back(';');
            while (priority(stack[top]) >= priority(infix[i])) {
                postfix.push_back(stack[top--]);
                postfix.push_back(';');
            }
            stack[++top] = infix[i]; // in stack
            break;

        case ')':
            while (stack[top] != '(') { // when encounter ) output to ( 
                postfix.push_back(';');
                postfix.push_back(stack[top--]);
            }
            top--;  // no output ( 
            break;
        case ';':
            postfix.push_back(';');
            break;
        case '.':
            postfix.push_back('.');
            break;
        default:  // directly output
            postfix.push_back(infix[i]);
        }

    }
    while (top > 0) {
        postfix.push_back(stack[top--]);
        postfix.push_back(';');
    }
    //postfix.push_back(';');
    string nonono = ";;";
    size_t f = postfix.find(nonono);
    string Error = "Error";
    if (f != string::npos) {
        cout << "Wrong input." << endl;
        postfix.clear();
        postfix.insert(0, ";Error;");
    }
    //cout << "inToPostfix's cout: " << postfix << endl;
}

int priority(char op) {
    switch (op) {
    case '+': case '-': return 1 ;
    case '*': case '/': return 2;
    case '^':return 3;
    case '!':return 4;
    default:            return 0;
    }
}


