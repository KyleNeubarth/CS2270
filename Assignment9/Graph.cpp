#include "Graph.h"
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < int(vertices.size()); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < int(vertices.size()); j++){
                if(vertices[j].name == v2 && i != j){
                    //add vert one way
                    adjVertex vert1;
                    vert1.v = &vertices[j];
                    vert1.weight = weight;
                    //opposite way
                    adjVertex vert2;
                    vert2.v = &vertices[i];
                    vert2.weight = weight;
                    //vertices[i].adj.push_back(vert1);
                    vertices[j].adj.push_back(vert2);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < int(vertices.size()); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" already in the graph."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.districtID = 0;
        vertices.push_back(v);

    }
}

/*int Graph::isAdjacent(std::string v1, std::string v2) {
    for(int i = 0; i < int(vertices.size()); i++){
        if (vertices[i].name == v1) {
            for(int j = 0; j < int(vertices[i].adj.size()); j++){
                if (vertices[i].adj[j].v->name == v2) {
                    return 1;
                }
            }
        }
    }
    return 0;
}*/

void Graph::DFSLabel(string startingCity, int distID) {

}

void DFSLabelHelp(vertex* start, int id) {
    start->districtID = id;
    for (int i=0;i<int(start->adj.size());i++) {
        if (start->adj[i].v->districtID == -1) {
            DFSLabelHelp(start->adj[i].v,id);
        }
    }
}

void Graph::assignDistricts() {
    int num = 1;
    for (int i=0;i<int(vertices.size());i++) {
        if (vertices[i].districtID == -1) {
            DFSLabelHelp( &(vertices[i]),num);
            num++;
        }
    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < int(vertices.size()); i++){
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < int(vertices[i].adj.size()); j++){
            cout<<vertices[i].adj[j].v->name << "(" << vertices[i].adj[j].weight << " miles)";
            if (j != int(vertices[i].adj.size()-1)) {
                cout <<"***"; 
            }
        }
        cout<<endl;
    }

}

//helper function for shortest path
void pathRecurse(vertex* current) {
    if (current->parent) {
        pathRecurse(current->parent);
    }
    cout << ", " <<current->name;
}

void Graph::shortestPath(string startingCity, string endingCity) {
    vertex* start;
    vertex* end;
    for (int i=0; i<(int)(vertices.size());i++) {
        //vertices are given a huge distance, so they will not be picked before they are actually calculated
        vertices[i].visited = false;
        vertices[i].unweightedDistance = 9999999;
        if (vertices[i].name == startingCity) {
            start = &vertices[i];
            start->unweightedDistance = 0;
        }
        if (vertices[i].name == endingCity) {
            end = &vertices[i];
        }
    }
    /*for (int i=0; i<(int)(vertices.size());i++) {
        if (vertices[i].districtID == start->districtID) {
            cout << vertices[i].name << ";";
        }
        
    }
    cout << "\n";*/
    if (!start || !end) {
        cout << "One or more cities doesn't exist";
        return;
    }
    if (start->districtID == -1 || start->districtID == -1) {
        cout << "Please identify the districts before checking distances";
        return;
    }
    if (start->districtID != end->districtID) {
        cout << "No safe path between cities";
        return;
    }


    bool running = true;

    vertex* node = start;

    while (running) {

        for (int i=0; i<(int)(vertices.size());i++) {
            //unvisited and in the same district?
            if (vertices[i].visited == false && vertices[i].districtID == start->districtID) {
                
                //cout << vertices[i].name << "~" << vertices[i].unweightedDistance << ";";
                
                //to find node with least distance, compare. If there is no least, automatically add
                if (!node || vertices[i].unweightedDistance < node->unweightedDistance) {
                    node = &vertices[i];
                }
            }
        }
        //exit condition
        if (!node) {
            //cout << "\nbreaking\n";
            running = false;
            continue;
        }
        
        //cout << "\n--" << node->name << "--\n";
        for (int i=0;i<(int)(node->adj.size());i++) {
            //if node has not been visited, calculate distance
            if (!node->adj[i].v->visited && node->adj[i].weight != -1 && node->adj[i].v->unweightedDistance == 9999999) {
                node->adj[i].v->unweightedDistance = node->unweightedDistance + 1;
                //set parent for later printout
                node->adj[i].v->parent = node;
                //cout <<  "X" <<node->adj[i].v->name << ";" << node->adj[i].v->unweightedDistance << "X";
            }
        }
        //get ready for next step
        node->visited = true;
        node = nullptr;
    }    
    //print all the names
    //cout << "printing names\n";
    cout << end->unweightedDistance;
    pathRecurse(end);
    cout << "\n";
}

void Graph::shortestWeightedPath(string startingCity, string endingCity) {
    vertex* start;
    vertex* end;
    for (int i=0; i<(int)(vertices.size());i++) {
        //vertices are given a huge distance, so they will not be picked before they are actually calculated
        vertices[i].visited = false;
        vertices[i].weightedDistance = 9999999;
        if (vertices[i].name == startingCity) {
            start = &vertices[i];
            start->weightedDistance = 0;
        }
        if (vertices[i].name == endingCity) {
            end = &vertices[i];
        }
    }
    /*for (int i=0; i<(int)(vertices.size());i++) {
        if (vertices[i].districtID == start->districtID) {
            cout << vertices[i].name << ";";
        }
        
    }
    cout << "\n";*/
    if (!start) {
        cout << "city not found.";
        return;
    }
    if (start->districtID == -1 || start->districtID == -1) {
        cout << "Please identify the districts before checking distances";
        return;
    }
    if (start->districtID != end->districtID) {
        cout << "No safe path between cities";
        return;
    }


    bool running = true;

    vertex* node = start;

    while (running) {

        for (int i=0; i<(int)(vertices.size());i++) {
            //unvisited and in the same district?
            if (vertices[i].visited == false && vertices[i].districtID == start->districtID) {
                
                //cout << vertices[i].name << "~" << vertices[i].weightedDistance << ";";
                
                //to find node with least distance, compare. If there is no least, automatically add
                if (!node || vertices[i].weightedDistance < node->weightedDistance) {
                    node = &vertices[i];
                }
            }
        }
        //exit condition
        if (!node) {
            //cout << "\nbreaking\n";
            running = false;
            continue;
        }
        
        //cout << "\n--" << node->name << "--\n";
        for (int i=0;i<(int)(node->adj.size());i++) {
            //if node has not been visited, calculate distance
            if (!node->adj[i].v->visited && node->adj[i].weight != -1 && node->adj[i].v->weightedDistance == 9999999) {
                node->adj[i].v->weightedDistance = node->weightedDistance + node->adj[i].weight;
                //set parent for later printout
                node->adj[i].v->parent = node;
                //cout <<  "X" <<node->adj[i].v->name << ";" << node->adj[i].v->weightedDistance << "X";
            }
        }
        //get ready for next step
        node->visited = true;
        node = nullptr;
    }    
    //print all the names
    //cout << "printing names\n";
    cout << end->weightedDistance;
    pathRecurse(end);
    cout << "\n";
}