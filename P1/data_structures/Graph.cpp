//
// Created by stani on 06.10.2023.
//

#include "Graph.h"
using namespace std;

/**
 * Loading data from selected file. The file is selected inside this function.
 * @param fileName String name of .txt file (should be given with .txt extension)
 */
void Graph::loadData() {

    cout<<"\n\n";

    string fileName;

    cout<<"Prosze podac nazwe pliku: ";
    cin>>fileName;
    if( fileName[fileName.size()-3] != 't' or fileName[fileName.size()-2] != 'x' or fileName [fileName.size()-1] != 't' ){
        fileName = fileName + ".txt";
    }

    fileName = R"(D:\PWR\4 sem\SDIZO\Projekt2\dane.txt)";

    ifstream fin;

    fin.open(fileName.c_str(), ios::in);
    fin >> numOfVertices;




    Graph::v = new int *[numOfVertices];

    // filling the structure with data
    for(int i =0; i < numOfVertices; i++){
        v[i] = new int [numOfVertices];             // Tworzenie dwuwymiarowej tablicy - dokladanie drugiego wymiaru
        for(int j =0; j < numOfVertices; j++){
            if(i == j){
                v[i][j] = 0;
            }
            else{
                fin >> v[i][j];
            }
        }
    }

}


/**
 * Printing adjustment table of graph
 */
void Graph::printGraph(){

    for(int i =0; i < Graph::numOfVertices; i++){
        v[i] = new int [numOfVertices];             // Tworzenie dwuwymiarowej tablicy - dokladanie drugiego wymiaru
        for(int j =0; j < numOfVertices; j++){
          cout<<v[i][j] << " ";                     //TODO: tu przydałoby sie wyrównywanie do 3 miejsc np.
        }
        cout<<endl;
    }
}

