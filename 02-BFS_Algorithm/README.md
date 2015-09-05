# 02 Breadth-First Search Algorithm

1. usage:  
    This is to read the input file to create the network.
    Please enter the input file name.  
    Screen Input: network filename , s (source node), t (sink node)  
    Screen Output:   
        (1) all the reachable nodes and their distance labels from s by the BFS labeling order   
        (2) all the paths from s to t  
2. input file:   
    test1.sp  
    test2.sp

3. output files:  
    nope
 
4. compile:  
    g++ main.cpp  
    ./a.out

##Function Pseudocode:  
Class ParseNetworkFile   
**readFile(fileName)**  
```
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
                              and resize point[] by node number
                    case 'a': store the arc, from, to and arc id by counting
```
---  
**ForwardStar_assignStartPoint **  
```
        call  sort(arcs.begin(), arcs.end(), mySortFunctionByTail);
``` 
---  
**mySortFunctionByTail(a1,a2)**  
```
        if a1.tail != a2.tail
            do return (a1.tail < a2.tail)
        else do return (a1.head < a2.head)
```  
---  
**ForwardStar_assignStartPoint **  
```
        call  sort(arcs.begin(), arcs.end(), mySortFunctionByTail);
        use point[] to record different start node(when we meet new tail)
```
---  
**BFS(int sourceNodeNo)**    
```
        queue <int> q
        bool visitStatus[nodeNumber+1];
        int DistanceLabel[nodeNumber+1];
        while(q is not empty){
            distance = DistanceLabel[currentNode]+1;
            q.pop();
            for(int i=point[currentNode]; i<point[currentNode+1];i++)
                if(visitStatus is admissable){
                    DistanceLabel[to]= distance;
                    visitStatus[to]=true;
                    q.push(to);
                cout<<to<<"["<<DistanceLabel[to]<<"] ";
```
---  
**DFS(int sNodeNo, int tNodeNo)**  
```
        initialize visitStatus, shortestPathLength
        push sNodeNo to currentPath
        call DFS_traversal(sNodeNo, tNodeNo) & call printALLPath(sNodeNo, tNodeNo)
``` 
---  
**DFS_traversal(int sNodeNo, int tNodeNo)**  
```
        //recursive DFS_traversal
        for( int fromIndex = point[sNodeNo] ; fromIndex < point[sNodeNo+1]; fromIndex++ ) do
            if (next_point's visitStatus is admissable)  do
                currentPath.push_back(next_point)
                visitStatus[next_point] = true; //change status to visted
                DFS_traversal(to, tNodeNo);
                visitStatus[to] = false;
                currentPath.pop_back();
        if the last node in currentPath == tNodeNo do
                add the currentPath to allPaths vector
                and update the shortestPathLength
```
---  
**printAllPath(int source, int sink)**   
```
        print all possible paths in allPaths vector
        if find the current path size  == shortestPathLength
            print out *
``` 
coded by Chia-Jung Hsu, ID: h34006157, email: grace828822@gmail.com
