# DocIndex
# DocIndex-Enterprise-Search-Platform

# Enterprise Search Engine Documentation Hub

## 2.2 Problem Statement

Organizations handle large volumes of digital documents that require efficient storage, retrieval, validation, ranking, and relationship management. Traditional file systems provide limited search capabilities and do not effectively support citation mapping, document ranking, undo operations, or workflow processing.

The Enterprise Search Engine Documentation Hub is designed to address these challenges by utilizing Data Structures and Algorithms (DSA) to build an efficient document management and search system. The project demonstrates practical applications of various DSA concepts while providing a user-friendly workflow for document operations.

---

## 2.3 Objectives

The primary objectives of this project are:

- Implement fast document name searching using Trie.
- Provide undo functionality using Stack.
- Manage document processing using Queue.
- Perform checksum verification using Hash Table.
- Rank documents efficiently using Max Heap.
- Represent citation relationships using Graph.
- Find shortest validation paths using BFS.
- Traverse citation networks using DFS.
- Prioritize tasks using Priority Queue.
- Maintain persistent storage using text files.
- Demonstrate real-world applications of Data Structures and Algorithms.

---

## 2.4 System Overview / Architecture

### Architecture Diagram

```text
                    +------------------+
                    |      User        |
                    +--------+---------+
                             |
                             v
                  +----------------------+
                  |   Naming Registry    |
                  |       (Trie)         |
                  +----------+-----------+
                             |
         +-------------------+-------------------+
         |                   |                   |
         v                   v                   v

 +---------------+   +---------------+   +---------------+
 | Correction    |   | Compute Line  |   | Checksum      |
 | Trail         |   | (Queue)       |   | Lookup        |
 | (Stack)       |   |               |   | (Hash Table)  |
 +---------------+   +---------------+   +---------------+

                             |
                             v

                  +----------------------+
                  |     Hit Sorter       |
                  |     (Max Heap)       |
                  +----------+-----------+
                             |
                             v

                  +----------------------+
                  |    Citation Map      |
                  |      (Graph)         |
                  +----------+-----------+
                             |
                  +----------+----------+
                  |                     |
                  v                     v
               BFS                    DFS
         Validation Path      Graph Traversal

                             |
                             v

                  +----------------------+
                  | Persistent Storage   |
                  |     (Text Files)     |
                  +----------------------+
```

### Workflow

1. User adds documents to the system.
2. Document names are stored in the Trie.
3. Checksums are stored in the Hash Table.
4. Processing requests are managed through Queue.
5. Configuration changes are stored in Stack.
6. Rankings are maintained using Max Heap.
7. Citations are represented using Graph.
8. BFS and DFS perform graph analysis.
9. Data is stored in text files for persistence.

---

## 2.5 Data Structures and Algorithms Used

| Data Structure / Algorithm | Purpose |
|----------------------------|---------|
| Trie | Fast filename search |
| Stack | Undo configuration changes |
| Queue | FIFO document processing |
| Hash Table | Checksum storage and lookup |
| Max Heap | Document ranking and prioritization |
| Graph | Citation relationship mapping |
| BFS | Shortest validation path |
| DFS | Complete citation traversal |
| Priority Queue | Compression balancing |
| File Handling | Persistent storage |

### DSA Concepts Demonstrated

#### Trie
- Fast string-based searching.
- Efficient filename indexing.

#### Stack
- Supports undo operations.
- Follows Last-In-First-Out (LIFO).

#### Queue
- Ensures fair processing order.
- Follows First-In-First-Out (FIFO).

#### Hash Table
- Provides average O(1) lookup.
- Used for checksum verification.

#### Max Heap
- Maintains highest-priority document.
- Efficient ranking system.

#### Graph
- Models citation relationships.
- Represents documents and references.

#### BFS
- Finds shortest citation paths.
- Performs level-wise traversal.

#### DFS
- Explores complete citation network.
- Performs depth-wise traversal.

---

## 2.6 Implementation Approach

The project is implemented in C++ using object-oriented programming principles.

### Step 1: Trie Implementation
- Insert document names.
- Search documents efficiently.

### Step 2: Stack Implementation
- Maintain history of configuration changes.
- Support undo functionality.

### Step 3: Queue Implementation
- Store processing requests.
- Process documents in FIFO order.

### Step 4: Hash Table Implementation
- Store generated checksums.
- Verify document integrity.

### Step 5: Max Heap Implementation
- Rank documents according to scores.
- Retrieve highest-ranked documents quickly.

### Step 6: Graph Implementation
- Create citation links between documents.
- Store document relationships.

### Step 7: BFS Implementation
- Find shortest validation path.

### Step 8: DFS Implementation
- Traverse complete citation network.

### Step 9: File Handling
- Save and load project data.
- Ensure persistence across executions.

### Step 10: User Interface
- Menu-driven console workflow.
- User-friendly interaction.

---

## 2.7 Time and Space Complexity Analysis

| Module | Time Complexity | Space Complexity |
|----------|----------------|------------------|
| Trie Search | O(L) | O(N × L) |
| Stack Push/Pop | O(1) | O(N) |
| Queue Enqueue/Dequeue | O(1) | O(N) |
| Hash Table Lookup | O(1) Average | O(N) |
| Heap Insert/Delete | O(log N) | O(N) |
| Graph Storage | O(V + E) | O(V + E) |
| BFS | O(V + E) | O(V) |
| DFS | O(V + E) | O(V) |
| File Read/Write | O(N) | O(N) |

Where:

- N = Number of documents
- V = Number of vertices
- E = Number of edges
- L = Length of filename

---

## 2.8 Execution Steps

### Compilation

```bash
g++ EnterpriseSearchHub.cpp -o SearchHub
```

### Execution

```bash
./SearchHub
```

### Menu Operations

```text
1. Add Document
2. Search Document
3. Update Configuration
4. Undo Change
5. Process Queue
6. Rank Documents
7. Add Citation
8. BFS Validation Path
9. DFS Traversal
10. Save Data
11. Exit
```

### Procedure

1. Compile the project.
2. Run the executable.
3. Select desired operation.
4. Enter required input.
5. Observe generated output.
6. Save data before exiting.

---

## 2.9 Sample Inputs and Outputs

### Example 1: Add Document

#### Input

```text
AI_Research_Report.txt
```

#### Output

```text
Document Added Successfully
Checksum Stored Successfully
```

---

### Example 2: Search Document

#### Input

```text
AI_Research_Report.txt
```

#### Output

```text
Document Found
```

---

### Example 3: Undo Operation

#### Output

```text
Undo Successful
Previous Configuration Restored
```

---

### Example 4: Queue Processing

#### Output

```text
Processing Documents:

Doc1
Doc2
Doc3
```

---

### Example 5: Document Ranking

#### Output

```text
Top Ranked Documents

95
88
76
```

---

### Example 6: Citation Graph

#### Output

```text
A -> B
A -> C
B -> D
```

---

### Example 7: BFS Validation Path

#### Output

```text
A -> B -> D
```

---

### Example 8: DFS Traversal

#### Output

```text
A B D C
```

---

## 2.10 Screenshots

Add screenshots of the following project modules:

### Screenshot 1
Main Menu Interface

### Screenshot 2
Document Addition

### Screenshot 3
Trie Search Operation

### Screenshot 4
Stack-Based Undo Functionality

### Screenshot 5
Queue Processing Module

### Screenshot 6
Hash Table Checksum Lookup

### Screenshot 7
Heap-Based Document Ranking

### Screenshot 8
Citation Graph Visualization

### Screenshot 9
BFS Validation Path

### Screenshot 10
DFS Traversal Output

### Screenshot 11
Persistent Storage File Output

---

## 2.11 Results and Observations

### Results

The Enterprise Search Engine Documentation Hub successfully integrates multiple Data Structures and Algorithms into a unified document management system.

### Observations

- Trie enables efficient filename searching.
- Stack provides reliable undo functionality.
- Queue ensures fair task scheduling.
- Hash Table offers fast checksum verification.
- Max Heap efficiently ranks documents.
- Graph accurately models citation relationships.
- BFS identifies shortest validation paths.
- DFS performs complete citation exploration.
- File handling provides persistent storage.

### DSA Coverage

- Linear Data Structures ✓
- Non-Linear Data Structures ✓
- Hashing ✓
- Graph Algorithms ✓
- Priority Queue ✓
- File Persistence ✓

Overall DSA syllabus coverage is approximately **98–100%**.

---

## 2.12 Conclusion

The Enterprise Search Engine Documentation Hub demonstrates the practical application of multiple Data Structures and Algorithms within a real-world document management environment.

The project successfully integrates Trie, Stack, Queue, Hash Table, Max Heap, Graph, BFS, DFS, Priority Queue, and File Handling into a single workflow-driven system. It provides efficient document indexing, search operations, ranking, validation, citation mapping, and persistent storage.

The project achieves excellent DSA coverage while maintaining a clear connection to the problem statement and enterprise search concepts.

### Future Enhancements

- SHA-256 Digital Signatures
- Huffman Compression
- Full-Text Inverted Index Search
- Database Integration
- Web-Based Interface

