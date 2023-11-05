//
// Created by stani on 06.10.2023.
//

#include "Graph.h"
using namespace std;


/**
 * Loading data from selected file. The file is selected inside this function.
 * @param fileName String name of .txt file (should be given with .txt extension)
 */
bool Graph::loadData(string fileName) {

    if( fileName[fileName.size()-3] != 't' or fileName[fileName.size()-2] != 'x' or fileName [fileName.size()-1] != 't' ){
        fileName = fileName + ".txt";
    }

    fileName = R"(..\data\)" + fileName;
    ifstream fin;

    try {
        fin.open(fileName.c_str(), ios::in);

        if (!fin.is_open()) {
            throw std::ifstream::failure("\nFailed to open the file\n");
        }

        fin >> numOfVertices;

        Graph::v = new int *[numOfVertices];

        // filling the structure with data
        for(int i = 0; i < numOfVertices; i++){
            v[i] = new int [numOfVertices];             // creating 2nd dim of matrix
            for(int j = 0; j < numOfVertices; j++){
                fin >> v[i][j];
            }
        }
        fin.close();

    } catch (const std::ifstream::failure& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
        std::cout<<"\nWrong filename. Try again\n";
        return false;
    }


    return true;
}


/**
 * Printing adjacency matrix of graph
 */
void Graph::printGraph(){

    for(int i = 0; i < Graph::numOfVertices; i++){
        for(int j = 0; j < numOfVertices; j++){
          cout<<v[i][j] << " ";                     //TODO: tu przydałoby sie wyrównywanie do 3 miejsc np.
        }
        cout<<endl;
    }
}

/**
 * Function for returning size (number of vertices) of graph
 * @return int: number of vertices in graph
 */
int Graph::getSize() {
    return numOfVertices;
}

/**
 * Function for returning 2D array of vertices.
 * @return 2D array of ints
 */
int **Graph::getMatrix(){
    return v;
}

