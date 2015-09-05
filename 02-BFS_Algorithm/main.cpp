#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

struct arcDataType //Define a new Data Type to use dynamic storage
{
    //Constructer
    arcDataType() {
        tail = -1;
        head = -1;
        arcLength = INT_MAX;
    };
    
    int tail;
    int head;
    double arcLength;
    
     arcDataType(int _tail, int _head, double _arcLength){
        //setter
        tail = _tail;
        head = _head;
        arcLength = _arcLength;
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
        int tail, head;
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
                    point.resize(nodeNumber+2);
                    break;
            
                case 'a':
                    tail = stoi(lineElement[1]);        // Using the stoi() to convert the string to int
                    head = stoi(lineElement[2]);        // Using the stoi() to convert the string to int
                    arcLength = stod(lineElement[3]);   // Using the stoi() to convert the string to double
                    arcs.push_back(arcDataType(tail, head, arcLength));
                    break;
                    
                default:
                    break;
                }
        }file.close();
    }
    
    static bool mySortFunctionByTail(arcDataType a1, arcDataType a2) //Re-difine the sort function
    {
        if(a1.tail != a2.tail)
            return (a1.tail < a2.tail);
        else
            return (a1.head < a2.head);
    }
    
//    static bool mySortFunctionByHead(arcDataType a1, arcDataType a2) //Re-difine the sort function
//    {
//        if(a1.head != a2.head)
//            return (a1.head < a2.head);
//        else
//            return (a1.tail < a2.tail);
//    }
    
    void ForwardStar_assignStartPoint()
    {
        //before doing the point assignment, sort the arc by order
        sort(arcs.begin(), arcs.end(), mySortFunctionByTail);
        //initialize
        for(int i=0;i<arcs[0].tail+1; i++)
            point[i]=0;
        
        int currentNode = arcs[0].tail;
        int nextNode = arcs[1].tail;
        point[currentNode] =0;
        
        for (int i = 0; i < (int)arcs.size()-1;i++){
            currentNode = arcs[i].tail;
            nextNode = arcs[i+1].tail;
            if(currentNode < nextNode)
                for(int j = currentNode+1; j<nextNode+1; j++)
                    point[j]=i+1;
        }
        
        for(int i=currentNode+1; i<nodeNumber+2;i++)
            point[i]=(int)arcs.size();
    }

    
//BFS part
    void BFS(int sourceNodeNo)
    {
        queue <int> q;

        //initialize
        bool visitStatus[nodeNumber+1];
        for (int i=0; i<nodeNumber+1; i++)
            visitStatus[i]= false;
        
        int distance = 0;
        int DistanceLabel[nodeNumber+1];
        for (int i=0; i<nodeNumber+1; i++)
            DistanceLabel[i]= -1;
        
        q.push(sourceNodeNo);
        visitStatus[sourceNodeNo]=true;
        DistanceLabel[sourceNodeNo]=0;
        cout<< "BFS: "<<sourceNodeNo<<"["<<DistanceLabel[sourceNodeNo]<<"] ";
        
        //process the queue until it is empty
        int currentNode, from, to;
        while(!q.empty()){
            currentNode =  q.front();
            distance = DistanceLabel[currentNode]+1;
            q.pop();
            //using point to help realize the BFS
            for(int i=point[currentNode]; i<point[currentNode+1];i++){
                from = arcs[i].tail;
                to = arcs[i].head;
                if(visitStatus[to]==false)  //if "to" is admissible
                {
                    DistanceLabel[to]= distance;    //Distance update
                    visitStatus[to]=true;           //change the status to visited
                    q.push(to);                     //push "to" to queue
                    cout<<to<<"["<<DistanceLabel[to]<<"] ";
                }
            }
        }
       cout << endl;
    }
    
//DFS part
    void DFS(int sNodeNo, int tNodeNo)
    {
        //initialize
        visitStatus.resize(nodeNumber+1);
        visitStatus[sNodeNo] = true;
        currentPath.push_back(sNodeNo);
        shortestPathLength = INT_MAX;
        
        //call function
        DFS_traversal(sNodeNo, tNodeNo);
        printAllPath(sNodeNo, tNodeNo);
    }
    
    void DFS_traversal(int sNodeNo, int tNodeNo){
        int to;
        for( int fromIndex = point[sNodeNo] ; fromIndex < point[sNodeNo+1]; fromIndex++ ){
            to = arcs[fromIndex].head;
            if (visitStatus[to]==false) {
                currentPath.push_back(to);  //push "to" to currentPath
                visitStatus[to] = true;     //change status to visted
                DFS_traversal(to, tNodeNo); // call itself to do the recursive
                visitStatus[to] = false;    //change status to not visted(admissible)
                currentPath.pop_back();     //pop "to" from currentPath(using Stack idea)
            }
        }
        
        if (currentPath.back() == tNodeNo) //if the last node in current path == sink node
        {
            allPaths.push_back(currentPath);    //store the currentPath to allPath vector
            if (shortestPathLength > currentPath.size()-1) //check whether path length is minimum
                // if not minimum, update by currenPath size
                shortestPathLength = (int)currentPath.size()-1;
            return;
        }
    }
    
    void printAllPath(int source, int sink)
    {
        //Print total numbers of path from source to sink
        cout<< source << "->" << sink << ": "<< allPaths.size()<<" paths." <<endl;
        
        //Print each path by vector currentPath in vector allPaths
        for (int i = 0; i < allPaths.size(); i++) {
            if (allPaths[i].size()-1 == shortestPathLength)//if we meet the shortestPath, add "*"
                            cout << "*";
            cout << "["<< allPaths[i].size()-1 << "]: "<< allPaths[i][0];
            for (int j = 1; j < allPaths[i].size(); j++)
                cout << "-" << allPaths[i][j];
            cout << endl;
        }
        cout<<endl;
    }
    
    private:
        string problemName, problemType;
        int nodeNumber,arcNumber,shortestPathLength;
        vector<int>point;
        vector<arcDataType>arcs;
        vector<bool>visitStatus;
        vector< vector<int> >allPaths;
        vector<int>currentPath;
};


int main() {
    
    string fileName;
    int sourceNodeNo;
    int sinkNodeNo;
    ParseNetworkFile networkFile;
    
    cout << "Please input network filename: ";
    cin >> fileName;
    //networkFile.readFile("test1.sp");
    
    cout << "Please input source node: ";
    cin >> sourceNodeNo;
    
    cout << "Please input sink node: ";
    cin >> sinkNodeNo;
    
    networkFile.readFile(fileName);
    networkFile.ForwardStar_assignStartPoint();
    networkFile.BFS(sourceNodeNo);
    networkFile.DFS(sourceNodeNo,sinkNodeNo);
    
    return 0;
}
