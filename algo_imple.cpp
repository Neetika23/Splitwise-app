#include <iostream>
#include<set>
using namespace std;
int main() {
    
    int no_of_transactions,friends;
    cin>>no_of_transactions>>friends;

    int x,y,amount;   //amount x gives to y

    //Make multiarray to store net amt that each person will have to take at the end.
    int net[100000] = {0};
    
    while(no_of_transactions--){
        cin>>x>>y>>amount;
        
        //calculating net of every person.
        net[x] -= amount;
        net[y] += amount;
    }
    
    multiset<int> m;   //multiset is used because it is possible that we could have multiple transactions (multiple net balances) of same value.
    
    //initialise the multiset.
    for(int i=0;i<friends;i++){
        if(net[i]!=0){
            m.insert(net[i]);
        }
    }
    
    int cnt = 0; //count for transactions so that if only 2 transactions are left, both will have same values and will directly become zero.
    
    //This greedy approach i.e. the person with highest debit will give money to person with highest credit.
    //pop out two persons from left and right and try to settle them.
    while(!m.empty()){
        auto low = m.begin();
        auto high = prev(m.end());
        //m.end() will give pointer after the last pointer so to access the last one we used prev() since m.end()-1 is not supported.
        
        int debit = *low;
        int credit = *high;
        
        //Erase these from multiset and then try to make settlement between the two.
        m.erase(low);
        m.erase(high);
        
        //Settlement.
        int settlement_amt = min(-debit,credit);
        cnt++;
        
        //transfer settlement_amt from donor to acceptor.
        debit += settlement_amt;    
        //like if A has to give 50 and is receiving 30 so, -50+30 = -20, means A now have to only give rs 20 to some other person.
        
        credit -= settlement_amt;
        //One of them will be zero.
        
        
        //Now the newly left amt i.e. 20 for the above example needs to be again inserted in the multiset.
        if(debit!=0){
            m.insert(debit);
        }
        if(credit!=0){
            m.insert(credit);
        }
    }
    cout<<cnt<<endl;
}
