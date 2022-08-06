#include<iostream>
#include<stack>
using namespace std;
bool isoperator(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}
bool lore(char exp , char top)  // less or equal (priority)
{
    if(((exp == '+' || exp == '-') && (top == '*' || top == '/')))   // less order
        return true;
    else if(((exp == '+' || exp == '-') && ((top == '-' || top == '+'))))  // equal order (+,-)
        return true;   
    else if(((exp == '*' || exp == '/') && ((top == '*' || top == '/'))))   // equal order (*,/)
        return true;
    return false;
}
template<class t>
t evaluate(t op1 , t op2 , char sign)
{
    t result;
    switch(sign)
    {
        case '+' : 
            result = op1 + op2;
            break;
        case '-' : 
            result = op1 - op2;
            break;
        case '*' : 
            result = op1 * op2;
            break;
        case '/' : 
            result = op1 / op2;
            break;
    }
    return result;
}
void swap(stack<char>& st,string& exp , int index)
{
    char temp = exp[index];
    exp[index] = st.top();
    st.pop();
    st.push(temp);
}
int to_int(string& exp , char c , int& i)
{
    int number = 0;
    while(exp[i] >= '0' && exp[i] <= '9')
    {
        number = number * 10 + (exp[i] - '0');
        i++;
    }
    i--;
    return number;
}
int main()
{
    string exp;
    stack<char>modify;  
    stack<float>eval;
    cout << "Enter expression to be evaluated : ";
    getline(cin,exp);
    int s = exp.size();
    float result;
    // from infix to postfix expression
    for(int i = 0 ; i < s ; i++)
    {
        if(exp[i] == ' ')
            {exp[i] = '\0';continue;}
        if(isoperator(exp[i]) || exp[i] == '(' || exp[i] == ')')
        {
            if(exp[i] == '(' || exp[i] == ')' )
            {
                modify.push(exp[i]);
                if(exp[i] == ')')
                {
                    string s;
                    modify.pop();
                    while(modify.top() != '(')
                    {
                        s+=modify.top();
                        modify.pop();
                    }
                    modify.pop();
                    exp.insert(i,s);
                }
            }
            else if(modify.empty())
                {modify.push(exp[i]);exp[i] = ' ';}
            else
            {
                if(modify.top() == '(')
                    {modify.push(exp[i]);exp[i] = ' ';}
                else if(lore(exp[i],modify.top()))
                    {
                        swap(modify,exp,i);
                    }
                else
                {
                    modify.push(exp[i]);
                    exp[i] = ' ';
                }
            }
        }
    }
    //  End of postfix

    // add last oprators if it's
    while(!modify.empty()) // O(n)
    {
        exp+=modify.top();
        modify.pop();
    }
    // evaluate values
    for(int i = 0 ; i < exp.size() ; i++)
    {
        if(exp[i] == '\0' ||  exp[i] == ' '  || exp[i] == '(' || exp[i] == ')' )
            continue;
        if(isoperator(exp[i]))
        {
            float operand2 = eval.top();
            eval.pop();
            float operand1 = eval.top();
            eval.pop();
            result = evaluate(operand1 , operand2 , exp[i]);
            eval.push(result);
        }
        else
        {
            eval.push(to_int(exp , exp[i] , i));
        }
    }
    cout << "Answer = " << result << endl;
    return 0;
}