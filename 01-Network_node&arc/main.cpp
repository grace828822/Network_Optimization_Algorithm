/*
 This code can be compiled and run ok.
 
 usage:
    This is to read the input file to create the network.
    Please enter the input file name.
    And enter the sourcenode to see the connected arc with it.
 
 input file:
    test1.sp
    test2.sp
 
 output files:
    nope
 
 compile:
    g++ main.cpp
    ./a.out
 
 pseudocode:
 
    Class ParseNetworkFile
        -------------------------
        readFile(fileName)
        -------------------------
            ifstream file
            file.open(fileName)
 
            while(getline(file,eachLine))
                stringstream lineStream(eachLine)
                while (lineStream >> tmp)
                    lineElement.push_back(tmp)
                switch(identifier)
                    case 'c': ignore comments
                    case 't': store problem name
                    case 'p': store problem type, arcs, nodes
                    case 'n': store problem total node number 
                              and call initializeNetworkByNode(nodeNumber) to initialize network by node number
                    case 'a': store the arc, from, to and arc id by counting
        -------------------------
        initializeNetworkByNode(nodeNumber)
        -------------------------
            network.resize(nodeNum+1)
            for i < nodeNum+1
                network[i].resize(nodeNum+1)
 
        -------------------------
        searchNodeConnectedWithOthers(nodeNo)
        -------------------------
            if nodeNo < 1 OR nodeNo > nodeNumber
                print out "WARNING!!"
            else
                for i < nodeNumber+1
                    if (!(network[nodeNo][i]._arcLength <0)) // arc exist
                        connectedArcs.push_back(network[nodeNo][i])
                    if (!(network[i][nodeNo]._arcLength <0)) // arc exist
                        connectedArcs.push_back(network[i][nodeNo]);
            call mySortFunction(arc1, arc2)
            print connected arcs by arc_id
 
        -------------------------
        mySortFunction(arc1, arc2)
        -------------------------
            a1._id < a2._id
 
        -------------------------
 
 coded by Chia-Jung Hsu, ID: h34006157, email: grace828822@gmail.com
 date: 2015.03.23
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int arcID = 0;                      // Using arc ID to helps identify and sort the order

struct arcDataType //Define a new Data Type to use dynamic storage
{
    //Constructer
    arcDataType() {
        _arcLength = -1;
    };
    
    int _id;
    int _from;
    int _to;
    double _arcLength;
    
    arcDataType(int id, int from, int to, double arcLength)
    {
        //setter
        _id = id;
        _from = from;
        _to = to;
        _arcLength = arcLength;
    }
};

class ParseNetworkFile //Define a class ParseNetworkFile
{
    public:
    ParseNetworkFile(){ }//Constructer

    void readFile(string fileName)
    {
        //Declaration
        ifstream file;
        int from, to;
        double arcLength;
        string eachLine;

        file.open(fileName.c_str());
        
        while(getline(file, eachLine)) //start to parse the content line by line
        {
            //First, separating the word in each line
            stringstream lineStream(eachLine);  //Using stringstream to cut off the words (by blank)
            vector<string> lineElement;         //Using vector "lineElement" to store the separated words
            string tmp;                         //Create a tmp storage
            while (lineStream >> tmp)
                lineElement.push_back(tmp);     // add the new element to the end of the vector
            
            //Second, Using the beginning identifier to detect what to do
            char identifier = lineElement[0].at(0);
            switch(identifier){
                case 'c':
                    break;                              // ignore comments
            
                case 't':
                    problemName = lineElement[1];       // Store the problem name
                    break;
                
                case 'p':
                    problemType = lineElement[1];       // Store the problem type
                    nodeNumber = stoi(lineElement[2]);  // Using the stoi() to convert the string to int
                    arcNumber = stoi(lineElement[3]);   // Using the stoi() to convert the string to int
                    break;
                
                case 'n':
                    nodeNumber = stoi(lineElement[1]);  // Using the stoi() to convert the string to int
                    initializeNetworkByNode(nodeNumber);// Call initializeNetworkByNode function to initialize the network by nodeNumber
                    break;
            
                case 'a':
                    arcID++;                            // Use counter to specify the id of arc
                    from = stoi(lineElement[1]);        // Using the stoi() to convert the string to int
                    to = stoi(lineElement[2]);          // Using the stoi() to convert the string to int
                    arcLength = stod(lineElement[3]);   // Using the stoi() to convert the string to double
                    network[from][to]._arcLength = arcLength;//store the arcLength to the network dimensional vectors
                    network[from][to] = arcDataType(arcID, from, to, arcLength); //store data(arc ID, from, to and arcLength) to the network
                    break;
                    
                default:
                    break;
                
                }
        }
        file.close();
        
    }
    
    void initializeNetworkByNode(int nodeNum)
    {
        network.resize(nodeNum+1);               //Resize the network
        for (int i = 0; i < nodeNum+1; i++)
            network[i].resize(nodeNum+1);
    }

//-----------------Search Parts------------------//
    
    void searchArcsConnectedWithNode(int nodeNo) //search the arc which connected to the source node
    {
        if ( nodeNo < 1 || nodeNo > nodeNumber ) //Detecting the user input
            cout<<"!!Warning!!: node " << nodeNo << " does not exist!!" <<endl;
        else
        {
            vector<arcDataType> connectedArcs;
            for (int i = 0; i < nodeNumber+1 ; i++)
            {
                //There are two way needed to be detect whether "connect to" or "be connected with"
                if (!(network[nodeNo][i]._arcLength <0))        //if arcLength is not < 0 (meaning: arcLength>0), this arc exists
                    connectedArcs.push_back(network[nodeNo][i]);
                if (!(network[i][nodeNo]._arcLength <0))        //if arcLength is not < 0 (meaning: arcLength>0), this arc exists
                    connectedArcs.push_back(network[i][nodeNo]);
            }
            sort(connectedArcs.begin(), connectedArcs.end(), mySortFunction);   //Using the sort function to adjust the order of arcs by self-defined function
            for (int i=0; i<connectedArcs.size(); i++ )
            {
                cout << "arcs[" << connectedArcs[i]._id << "]: " << connectedArcs[i]._from << "-" << connectedArcs[i]._to << " : " << connectedArcs[i]._arcLength << endl ;
            }
        }
    }
    
    static bool mySortFunction(arcDataType a1, arcDataType a2) //Re-difine the sort function
    {
        return (a1._id < a2._id); //if arc1_id < arc2_id is true then return
    }
    
    private:
        string problemName, problemType;
        int nodeNumber, arcNumber;
        vector< vector<arcDataType> > network;  // n x n adjacency matrix

};


int main() {
    
    string fileName;
    int sourceNodeNo;
    ParseNetworkFile networkFile;
    
    cout << "Please input network filename: ";
    cin >> fileName;
    networkFile.readFile(fileName);
    
    cout << "Please input source node: ";
    cin >> sourceNodeNo;
    networkFile.searchArcsConnectedWithNode(sourceNodeNo);
    
    return 0;
}
