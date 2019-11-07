#include <stdio.h>
using namespace std;



class myString {
    private:  
        const int ACCURACY = 7;
        char *value;

        int myStrLen (char* source);
        int myStrLen (const char* source);
        void myStrCpy (const char *source, char* res);
        void myStrCpyPar (const char *source, char* res, int n);
        void pushBack(char ch);
        void pushFront(char ch);
        void popBack();

    public:
        myString(const char *input = "\0");
        myString(const myString &input, int n = -1);
        ~myString();
        void output();
        void FloatToString (float input);
        float StringToFloat ();  
};



int myString::myStrLen (char* source){
        int ans = 0;
        while (source[ans] != 0)
            ans++;
        return ans;
    }

int myString::myStrLen (const char* source){
    int ans = 0;
    while (source[ans] != 0)
        ans++;
    return ans;
}

void myString::myStrCpy (const char *source, char* res){
    for (int i=0; i<=myStrLen(source); i++)
        res[i] = source[i];
    return;
}

void myString::myStrCpyPar (const char *source, char* res, int n){
    for (int i=0; i<n; i++)
        res[i] = source[i];
    res[n] = 0;
    return;
}

void myString::pushBack(char ch){
    int len = myStrLen(value);
    char* res = new char[len+2];
    for (int i=0; i<len; i++)
        res[i] = value[i];
    res[len] = ch;
    res[len+1] = 0;
    delete[] value;
    value = res;
    return;
}

void myString::pushFront(char ch){
    int len = myStrLen(value);
    char* res = new char[len+2];
    for (int i=0; i<len; i++)
        res[i+1] = value[i];
    res[0] = ch;
    res[len+1] = 0;
    delete[] value;
    value = res;
    return;
}

void myString::popBack(){
    int len = myStrLen(value);
    char* res = new char[len-1];
    for (int i=0; i<len-1; i++)
        res[i] = value[i];
    res[len-1] = 0;
    delete[] value;
    value = res;
    return;
}

myString::myString(const char *input)
{
    value = new char[myStrLen(input)+1];
    myStrCpy(input, value);
    value[myStrLen(input)] = 0;
}

myString::myString(const myString &input, int n)
{
    if (n < 0) {
        value = new char[myStrLen(input.value)];
        myStrCpy(input.value, value);
    } else
    {
        value = new char[n];
        myStrCpyPar(input.value, value, n);
    };
}

myString::~myString(){
    delete[] value;
}

void myString::output(){
    printf("%s\n", value);
    return;
}

void myString::FloatToString (float input) {
    myString res;
    bool negative = false;
    if (input < 0) {negative = true; input = -input;}
    int int_inp = (int)input;
    if ( int_inp == 0 ) {res.pushFront('0');}
    while (int_inp > 0) {
        res.pushFront(int_inp%10 + '0');
        int_inp /= 10;
    }
    input -= (int)input;
    if (input > 0) {
        res.pushBack('.');
        for(int i=0; i<ACCURACY; i++) {
            input*= 10;
            res.pushBack((int)input + '0');
            input -= (int)input;
        }
        while (res.value[res.myStrLen(res.value)-1] == '0'){
            res.popBack();
        }
    }
    if (negative) {res.pushFront('-');}
    value = res.value;
    return;
}

float myString::StringToFloat (){
    float res = 0;
    bool negative = false;
    char* iter = value;
    if (*iter == '-') {negative = true; iter++;};
    while ((*iter != '.') && (*iter != 0)) {
        res *= 10;
        res += *iter -'0';
        iter++;
    }
    if(*iter == '.'){
        float j = 1;
        iter++;
        while (*iter != 0) {
            j /= 10;
            res += (*iter-'0')*j;
            iter++;   
        }
    }
    if (negative) {res = -res;}
    
    return res;
}   

int main(){
    myString empty_string;
    myString literal("copy this part<-- (14 symbols)");
    myString full_copy(literal);
    myString half_copy(literal, 14);

    myString float_str_1("-123.456");
    float str_to_float = float_str_1.StringToFloat();

    float float_to_str = -807.4;
    myString float_str_2;
    float_str_2.FloatToString(float_to_str);

    printf("=====================================================\n");
    printf("empty str: "); empty_string.output();
    printf("literal  : "); literal.output();
    printf("full copy: "); full_copy.output();
    printf("half copy: "); half_copy.output();
    printf("\n");

    printf("string (to float)  : "); float_str_1.output();
    printf("float (from string): %f\n", str_to_float);
    printf("\n");

    printf("float (to string)  : %f\n", float_to_str);
    printf("string (from float): "); float_str_2.output();
    printf("=====================================================\n");
    return 0;
}