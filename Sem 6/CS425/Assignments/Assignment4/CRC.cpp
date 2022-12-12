#include<bits/stdc++.h>
using namespace std;

void generate_data(int k,string &data){
     string temp = ""; 
     for(int i = 0;i<k; i++) {
     temp = temp + char(rand()%2+'0');
     }
     data = temp;
}
string generate_error(string D){
    int number_of_errors = 1+rand()%D.length();
    set <int>s;

    while(number_of_errors>0){
        int pos = rand()%D.length();
        if(s.find(pos)!=s.end()) continue;
        else{
            s.insert(pos);
            number_of_errors--;
            if(D[pos]=='0') D[pos]='1';
            else D[pos]='0';
        }
    }
    return D;
}
string division(string P, string Q) {
    string Remainder="";
    for(int i = 0;i<P.length();i++)
        Remainder+= char(int(Q[i]-'0') ^ int(P[i]-'0')+'0');
    for(int i = P.length();i<Q.length();i++){
        // cout<<Remainder<<endl;
        if(Remainder[0]=='1'){
            for(int j = 0;j<P.length();j++)
                Remainder[j] = char((int(Remainder[j]-'0') ^ int(P[j]-'0'))+'0');
        }
        Remainder+= Q[i];
        Remainder.erase(0,1);

    }
    if(Remainder[0]=='1')  {
        for(int j = 0;j<P.length();j++){
                Remainder[j] = char((int(Remainder[j]-'0') ^ int(P[j]-'0'))+'0');
        }
    }
    Remainder.erase(0,1);
    return Remainder;
    
}


int main(){
    
    string D,P,T,Q,Remainder,Error_D,Received_Remainder;
    srand((unsigned int)time(NULL));
    
    generate_data(10,D);
    cout<<"Data generated is: "<<D<<endl;
   
    P = "110101";  // CRC PAttern can be updated here
    cout << "Pattern provided is: "<< P<<endl;
   
    Q = D;
    for(int i = 0; i < P.length()-1;i++) {
        Q +='0';
    }
    Remainder = division(P,Q);
    cout<< "CRC pattern appended is: "<<Remainder<<endl;
    
    T = D+Remainder; 
    cout<< "Frame generated is: "<<T<<endl;
    
    Error_D = generate_error(D);
    cout<<"Frame transmitted with error is: "<<Error_D + Remainder<<endl;

    Received_Remainder = division(P,Error_D+Remainder);
    cout<<"Remainder Obtained is: "<<Received_Remainder<<endl;

    for(int i = 0;i<Received_Remainder.length();i++) 
        if(Received_Remainder[i]=='1') {
            cout<<"Frame Discared as Remainder is non-zero\n";
            break;
        }
        else if(i==Received_Remainder.length()-1) cout<<"Frame Accepted as Remainder is zero\n"; 
   
    return 0;
}