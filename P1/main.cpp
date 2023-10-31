#include <iostream>
#include "data_structures/Graph.h"
#include "data_structures/Stack.h"
#include "utils/Time.h"
#include "algorithms/BF.h"
#include "algorithms/DP.h"
#include "algorithms/DP2.h"
#include "algorithms/BB.h"
#include "algorithms/DPP.h"

using namespace std;
int main() {

//TESTING GRAPH
    Graph g;
    g.loadData("P1//data//data5.txt");
    g.printGraph();
    cout<<"\n\n------------------------------------------\n\n";

    BB bb(g);
//    bb.recursion(0);
//    bb.printResult();
    bb.run();


    DP dp(g);
//    dp.apply();
//    dp.printResult();
    dp.run();


    BF bf(g);
//    bf.recursion(0);
//    bf.printResult();
    bf.run();


//    Graph g;
//    g.loadData("P1//data//data3.txt");
//    g.printGraph();
//    cout<<"ROZMIAR GRAFU: "<<g.getSize()<<endl;
//    DP2 dp(g);
//    dp.apply();
//    cout<< dp.resultToString();

//    dp.heldKarp(0, 1);
//    dp.printTour(0);




//// TESTING STACK
//    Stack s;
//    Stack ss;
//    Time t;
//    t.start();
//    cout<<s.getSize()<<endl;
//    s.push_back(10);
//    s.push_back(11);
//    s.push_back(12);
//    cout<<s.getSize()<<endl;
//    s.pop_back();
//    cout<<s.getSize()<<endl;
//    s.toString();
//    ss.clear();
//    ss = s;
//    s.clear();
//    s.push_back(11111);
//    cout<<endl;
//    ss.toString();
//    cout<<endl;
//    s.toString();
//    ss.clear();
//    ss.push_back(1);
//    ss.push_back(2);
//    ss.push_back(3);
//    ss.push_back(4);
//    ss.toString();
//    cout<<endl;
//    ss.toStringFromBottom();
//    t.stop();
//    cout<<"CZAS: "<<t.returnTime();

    return 0;


}
