#include <iostream>
#include "data_structures/Graph.h"
#include "data_structures/Stack.h"
#include "utils/Time.h"
#include "algorithms/BF.h"
#include "algorithms/DP.h"
#include "algorithms/DP2.h"
#include "algorithms/BB.h"

using namespace std;
int main() {

//TESTING GRAPH
    Graph g;
    g.loadData("P1//data//data3.txt");
    g.printGraph();
    BB bb(g);
    bb.recursion(0);
    bb.print();


//    Graph g;
//    g.loadData("P1//data//data3.txt");
//    g.printGraph();
//    cout<<"ROZMIAR GRAFU: "<<g.getSize()<<endl;
//    DP2 dp(g);
//    dp.apply();
//    cout<< dp.toString();

//    dp.heldKarp(0, 1);
//    dp.printTour(0);




//// TESTING STACK
//    Stack s;
//    Stack ss;
//    Time t;
//    t.start();
//    cout<<s.getSize()<<endl;
//    s.push(10);
//    s.push(11);
//    s.push(12);
//    cout<<s.getSize()<<endl;
//    s.pop();
//    cout<<s.getSize()<<endl;
//    s.print();
//    ss.copy(s);
//    cout<<endl;
//    ss.print();
//    cout<<endl;
//    ss.clear();
//    ss.push(1);
//    ss.push(2);
//    ss.push(3);
//    ss.push(4);
//    ss.print();
//    cout<<endl;
//    ss.printFromBottom();
//    t.stop();
//    cout<<"CZAS: "<<t.returnTime();

    return 0;


}
