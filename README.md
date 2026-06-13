# DocIndex
# DocIndex-Enterprise-Search-Platform

School of Future Tech
Case Study Report    

DSA PROJECT REPORT
DocIndex-Enterprise Search Engine Documentation Hub
Problem Statement No: 72
Submitted By:
 Akshara Tanted
Roll no: 150096725124
University:
 ITM Skills University
Subject:
Data Structure & Algorithms with CPP

 Academic Year:
 2025–2026

                                                                    



1.Problem Statement
DocIndex is an enterprise search engine documentation hub designed for organizations managing millions of internal documents. The system must provide fast file name retrieval, keyword-based searching, instant rollback of search index configuration changes, sequential document processing, rapid file integrity verification, relevance-based result ranking, citation mapping among documents, shortest citation path validation, and intelligent compression prioritization.
Traditional approaches become inefficient as document volume grows, causing slow searches, difficult document tracking, and expensive integrity verification. The objective is to design an efficient solution using appropriate Data Structures and Algorithms in C++.

2. Objectives
The main objectives of the project are:
To implement fast file and folder name searching using Trie.
To provide configuration rollback functionality using Stack.
To process indexing jobs sequentially using Queue.
To verify file uniqueness efficiently using Hash Tables.
To rank search results based on keyword frequency using Max Heap.
To represent document references through a Graph.
To find the shortest citation chain using Breadth First Search (BFS).
To prioritize files for compression using Priority Queue/Heap.
To demonstrate real-world applications of Data Structures in enterprise search systems.




3. Design / Architecture



           










Data Structure Mapping
Feature
Data Structure
Naming Registry
Tree
Correction Trail
Stack
Compute Line
Queue
Checksum Lookup
Hash Table
Hit Sorter
Max Heap
Citation Map
Graph
Validation Path
BFS
Compression Balancer
Priority Queue




4. Algorithm Description
1. Tree Algorithm
Purpose: Fast prefix search of file names.
Steps
Insert each file name character by character.
Store characters in Tree nodes.
Traverse nodes according to user prefix.
Return all matching file names.

2. Stack Algorithm
Purpose: Undo search configuration changes.
Steps
Push every configuration change onto stack.
When undo is requested:
Pop top configuration.
Restore previous state.

3. Queue Algorithm
Purpose: Process indexing jobs in FIFO order.
Steps
Add incoming documents to queue.
Remove and process documents from front.
Continue until queue becomes empty.


4. Hash Table Algorithm
Purpose: Verify document uniqueness.
Steps
Generate checksum value.
Store checksum in hash table.
Search checksum directly.
Determine whether file already exists.

5. Max Heap Algorithm
Purpose: Rank documents by keyword frequency.
Steps
Insert documents with frequency score.
Maintain heap property.
Extract highest-frequency document first.

6. Graph Algorithm
Purpose: Build citation network.
Steps
Each document becomes a vertex.
Citations become edges.
Store graph using adjacency list.



7. BFS Algorithm
Purpose: Find shortest citation path.
Steps
Start from source document.
Visit neighboring documents level by level.
Stop when destination document is found.
Reconstruct shortest path.

8. Compression Heap Algorithm
Purpose: Select files with highest compression benefit.
Steps
Assign compression score.
Insert into max heap.
Extract highest priority files first.





5. Complexity Analysis
Operation
Data Structure
Time Complexity
Insert File Name
Trie
O(L)
Search Prefix
Trie
O(L)
Push Configuration
Stack
O(1)
Undo Configuration
Stack
O(1)
Enqueue Job
Queue
O(1)
Dequeue Job
Queue
O(1)
Checksum Search
Hash Table
O(1) Average
Insert Ranking Score
Heap
O(log n)
Extract Maximum
Heap
O(log n)
Add Citation Edge
Graph
O(1)
BFS Shortest Path
Graph
O(V + E)
Compression Priority Insert
Heap
O(log n)

Where:
L = Length of filename
V = Number of documents
E = Number of citations
n = Number of records

6. Screenshots of Execution
Insert the screenshots from your program execution here.
Suggested screenshots:
Figure 1
Main Menu
Figure 2
Trie File Search Output
Figure 3
Stack Undo Operation
Figure 4
Queue Processing
Figure 5
Hash Checksum Verification
Figure 6
Heap Ranking Results
Figure 7
Graph Citation Map
Figure 8
BFS Shortest Path Output
Figure 9
Compression Priority Results










7. Results and Findings
The developed system successfully demonstrates the use of multiple Data Structures and Algorithms in solving enterprise search engine challenges. Trie provided efficient file name searching, while Stack enabled quick rollback of configuration changes. Queue ensured ordered document processing, and Hash Table allowed rapid checksum verification.
The Max Heap effectively ranked documents according to keyword frequency. Graph representation successfully modeled document citations, and BFS efficiently identified the shortest citation path. The Compression Balancer prioritized files based on compression benefit. Overall, the project achieved all functional requirements specified in the problem statement.

8. Conclusion
The Enterprise Search Engine Documentation Hub was successfully designed and implemented using C++. The project demonstrates practical applications of Trie, Stack, Queue, Hash Table, Heap, Graph, and BFS in an enterprise-scale document management environment.
The system provides fast searching, configuration rollback, job scheduling, checksum verification, result ranking, citation mapping, shortest path discovery, and compression prioritization. These data structures significantly improve efficiency and scalability compared to conventional approaches.
Future enhancements may include implementation of real SHA-256 hashing, inverted indexing for full-text search, persistent storage using databases, and visualization of citation networks similar to enterprise platforms such as Elasticsearch and Confluence.
9. GitHub Repository















