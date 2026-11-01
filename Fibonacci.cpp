#include<iostream>
using namespace std;

//Recursive function to find the nth Fibonacci number
int fibonacci(int n) {
   if(n == 0){
    return 0;
   }
   if(n == 1){
    return 1;
   }
    return fibonacci(n - 1) + fibonacci(n - 2);
}
//Non Recursive function to find the nth Fibonacci number
int fibonacciNonRecursive(int n) {
    if(n == 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    int a = 0, b = 1, c;
    for(int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
int main(){
    int choice , n;

    do{
        cout<<"Fibonacci Series"<<endl;
        cout<<"1. Recursive"<<endl;
        cout<<"2. Non Recursive"<<endl;
        cout<<"3. Exit"<<endl;

        cout<<"Enter your choice:";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Enter the value of n:";
                cin>>n;
                cout<<"Fibonacci number at position "<<n<<" is: "<<fibonacci(n)<<endl;
                break;
            case 2:
                cout<<"Enter the value of n:";
                cin>>n;
                cout<<"Fibonacci number at position "<<n<<" is: "<<fibonacciNonRecursive(n)<<endl;
                break;
            case 3:
                cout<<"Exiting..."<<endl;
                break;
            default:
                cout<<"Invalid choice. Please try again."<<endl;
        }

    }while(choice != 3);
}