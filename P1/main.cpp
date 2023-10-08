#include <iostream>
#include "data_structures/Graph.h"
#include "data_structures/Stack.h"
#include "utils/Time.h"

using namespace std;
int main() {

//TESTING GRAPH
//    Graph g;
//    g.loadData("P1//data//data10.txt");
//    g.printGraph();
//    g.getSize();

// TESTING STACK
    Stack s;
    Time t;
    t.start();
    cout<<s.getSize()<<endl;
    s.push(10);
    s.push(11);
    s.push(12);
    cout<<s.getSize()<<endl;
    s.pop();
    cout<<s.getSize()<<endl;
    s.print();
    t.stop();
    cout<<"CZAS: "<<t.returnTime();

    return 0;


}
