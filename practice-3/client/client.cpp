#include <bits/stdc++.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<stdio.h>
#include<iostream>

using namespace std;

int atoi(const char* str)
{
    int sign = 1, base = 0, i = 0;
     
    // if whitespaces then ignore.
    while (str[i] == ' ')
    {
        i++;
    }
     
    // sign of number
    if (str[i] == '-' || str[i] == '+')
    {
        sign = 1 - 2 * (str[i++] == '-');
    }
   
    // checking for valid input
    while (str[i] >= '0' && str[i] <= '9')
    {
        // handling overflow test case
        if (base > INT_MAX / 10
            || (base == INT_MAX / 10
            && str[i] - '0' > 7))
        {
            if (sign == 1)
                return INT_MAX;
            else
                return INT_MIN;
        }
        base = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}

int main(int argc, char **argv){
    int r,k,n;
    r= atoi(argv[1]);
    k= atoi(argv[2]);
    n= atoi(argv[3]);

    cout<<argc<<"\n";
    cout<<r<<'\n'<<k<<'\n'<<n<<endl;
    cout<<*argv[1]<<'\n'<<argv[2]<<'\n'<<argv[3]<<endl;
}