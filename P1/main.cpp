#include <iostream>
#include "data_structures/Graph.h"
#include "data_structures/Stack.h"
#include "utils/Time.h"
#include "algorithms/BF.h"
#include "algorithms/DP.h"
#include "algorithms/BB.h"
#include "utils/Menu.h"
#include "data_structures/MyStack.h"

using namespace std;
int main() {

    Menu menu;
    menu.start();

/*
    Graph g;
    g.loadData("data10");
    g.printGraph();
    cout<<"\n\n------------------------------------------\n\n";




    BB bb(g);
    bb.run();
//
//
    DP dp(g);
    dp.run();


    BF bf(g);
    bf.run();
//    bf.run();
 */


//    Graph g;
//    g.loadData("P1//data//data3.txt");
//    g.printGraph();
//    cout<<"ROZMIAR GRAFU: "<<g.getSize()<<endl;
//    DP2 dp(g);
//    dp.apply();
//    cout<< dp.resultToString();

//    dp.heldKarp(0, 1);
//    dp.printTour(0);



/*
////// TESTING STACK
    MyStack s;
    MyStack ss;

    s.push_back(1);
    s.push_back(2);
    s.push_back(3);

    cout<<"Printing Stack s of size: " <<s.getSize()<<" containing (fb): " << s.toStringFromBottom()<<endl;


    ss.push_back(100);
    ss.push_back(200);
    ss.push_back(300);
    ss.push_back(400);

    cout<<"Printing Stack ss of size: " <<ss.getSize()<<" containing (fb): " << ss.toStringFromBottom()<<endl;

    cout<<"\n\n";

    s.copy(&ss);
    cout<<"Printing Stack s of size: " <<s.getSize()<<" containing (fb): " << s.toStringFromBottom()<<endl;
    cout<<"Printing Stack ss of size: " <<ss.getSize()<<" containing (fb): " << ss.toStringFromBottom()<<endl;
    s.push_back(4);
    s.push_back(5);
    ss.pop_back();
    ss.pop_back();

    cout<<"\n\n";

    cout<<"Printing Stack s of size: " <<s.getSize()<<" containing (fb): " << s.toStringFromBottom()<<endl;
    cout<<"Printing Stack ss of size: " <<ss.getSize()<<" containing (fb): " << ss.toStringFromBottom()<<endl;

    ss.copy(&s);

    cout<<"\n\n";

    cout<<"Printing Stack s of size: " <<s.getSize()<<" containing (fb): " << s.toStringFromBottom()<<endl;
    cout<<"Printing Stack ss of size: " <<ss.getSize()<<" containing (fb): " << ss.toStringFromBottom()<<endl;

    s.clear();
    ss.push_back(11);
    ss.copy(&s);

    cout<<"\n\n";

    cout<<"Printing Stack s of size: " <<s.getSize()<<" containing (fb): " << s.toStringFromBottom()<<endl;
    cout<<"Printing Stack ss of size: " <<ss.getSize()<<" containing (fb): " << ss.toStringFromBottom()<<endl;
*/

    return 0;


}
