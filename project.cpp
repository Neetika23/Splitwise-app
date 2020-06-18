#include <iostream>
#include<set>
#include<map>  //To store net balance of the person.
using namespace std;

//In this we will also tell about the transaction details.
//eg. A has to give rs. x to B, and so on.

class person_compare{
public:
    bool operator()(pair<string,int> p1, pair<string,int> p2){
        return p1.second < p2.second;
    }
};

int main() {
    
    int no_of_transactions,friends;
    cin>>no_of_transactions>>friends;

    string x,y;
    int amount;
    
    map<string,int> net;
    
    while(no_of_transactions--){
        cin>>x>>y>>amount;
        if(net.count(x)==0){
            net[x] = 0;
        }
        if(net.count(y)==0){
            net[y] = 0;
        }
        
        net[x] -= amount;
        net[y] += amount;
        
    }
    
    multiset<pair<string,int>, person_compare> m;
    //Iterate over person, add these in the multiset who have no zero set.
    for(auto p:net){
        string person = p.first;
        int amount = p.second;
        
        if(net[person]!=0){
            m.insert(make_pair(person,amount));  //now in multiset the comparisons will be done on the basis of first parameter, so either move amount at the first or make a custom func. to d so.
        }
    }
    
    //settlements , pop elements from start and end.
    int cnt = 0;
    while(!m.empty()){
        auto low = m.begin();
        auto high = prev(m.end());
        
        int debit = low->second;
        string debit_person = low->first;
        
        int credit = high->second;
        string credit_person = high->first;
        
        //pop them out.
        m.erase(low);
        m.erase(high);
        
        int settled_amount = min(-debit,credit);
        debit += settled_amount;
        credit -= settled_amount;
        
        //print transcations.
        cout<<debit_person<<" will pay "<<settled_amount<<" to the "<<credit_person<<endl;
        if(debit != 0){
            m.insert(make_pair(debit_person,debit));
        }
        if(credit != 0){
            m.insert(make_pair(credit_person,credit));
        }
        cnt += 1;
    }
    cout<<cnt<<endl;
    return 0;
}
