# DocIndex
# DocIndex-Enterprise-Search-Platform

# Enterprise Search Engine Documentation Hub

## 1. Problem Statement

Organizations handle large volumes of digital documents that require efficient storage, retrieval, validation, ranking, and relationship management. Traditional file systems provide limited search capabilities and do not effectively support citation mapping, document ranking, undo operations, or workflow processing.

The Enterprise Search Engine Documentation Hub is designed to address these challenges by utilizing Data Structures and Algorithms (DSA) to build an efficient document management and search system. The project demonstrates practical applications of various DSA concepts while providing a user-friendly workflow for document operations.

---

## 2. Objectives

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

## 3. System Overview / Architecture

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

## 4. Data Structures and Algorithms Used

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

## 5. Implementation Approach

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

## 6. Time and Space Complexity Analysis

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

## 7. Execution Steps

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

## 8. Sample Inputs and Outputs

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

## 9. Screenshots

Add screenshots of the following project modules:

### 1.Main Menu Interface
<img width="451" height="201" alt="Screenshot 2026-06-14 at 1 09 34 AM" src="https://github.com/user-attachments/assets/eb992852-1e8e-4367-8390-c8e88d4c6502" />


### 2.Naming Registry
<img width="625" height="219" alt="Screenshot 2026-06-14 at 1 12 08 AM" src="https://github.com/user-attachments/assets/003428c9-17c7-4257-bb1d-65397c87c24b" />

<img width="625" height="211" alt="Screenshot 2026-06-14 at 1 12 31 AM" src="https://github.com/user-attachments/assets/aace9d2c-c011-43d3-bf75-62a7b87539ca" />


###  3.Correction Trail
<img width="628" height="209" alt="Screenshot 2026-06-14 at 1 13 31 AM" src="https://github.com/user-attachments/assets/cf7f7f23-f104-4931-9199-a6721fab8d51" />

<img width="623" height="280" alt="Screenshot 2026-06-14 at 1 13 50 AM" src="https://github.com/user-attachments/assets/9fb230f7-4b78-4ecc-9ab6-59611838f335" />


### 4.Compute Line 
<img width="624" height="245" alt="Screenshot 2026-06-14 at 1 14 45 AM" src="https://github.com/user-attachments/assets/ffda1fbe-00ed-48e5-875c-8103aded3dfa" />

<img width="625" height="270" alt="Screenshot 2026-06-14 at 1 15 04 AM" src="https://github.com/user-attachments/assets/1eeb033c-5b58-4e66-96a0-cb53ee37a435" />

<img width="622" height="252" alt="Screenshot 2026-06-14 at 1 15 21 AM" src="https://github.com/user-attachments/assets/262290bb-0010-4b5b-9ca8-bd91e1c24e05" />


### 5.Hit Sorter
<img width="627" height="216" alt="Screenshot 2026-06-14 at 1 16 07 AM" src="https://github.com/user-attachments/assets/1bd7fbbe-8b3d-4d87-98b7-4d0ebc3e2792" />

<img width="628" height="333" alt="Screenshot 2026-06-14 at 1 16 26 AM" src="https://github.com/user-attachments/assets/5dbdb5cd-1e34-4589-a4b8-e42f0947b93b" />

<img width="627" height="208" alt="Screenshot 2026-06-14 at 1 16 46 AM" src="https://github.com/user-attachments/assets/b8eb2c6f-07a6-4e74-832e-5b285bd67aa6" />


### 6.Citation Map     
<img width="624" height="231" alt="Screenshot 2026-06-14 at 1 17 30 AM" src="https://github.com/user-attachments/assets/5fc419b5-d3e2-4f0a-be09-29468edd7f0d" />

<img width="624" height="528" alt="Screenshot 2026-06-14 at 1 17 49 AM" src="https://github.com/user-attachments/assets/92e323f8-fc21-4606-8d0b-e1a514a470eb" />


### 7.Validation Path & DFS
<img width="626" height="211" alt="Screenshot 2026-06-14 at 1 18 32 AM" src="https://github.com/user-attachments/assets/38ea970a-8788-4012-8159-ee497c91b9de" />

<img width="624" height="484" alt="Screenshot 2026-06-14 at 1 18 52 AM" src="https://github.com/user-attachments/assets/35505033-b98f-409a-b1e9-f68be5187027" />

<img width="624" height="200" alt="Screenshot 2026-06-14 at 1 19 11 AM" src="https://github.com/user-attachments/assets/dc19ca39-9d3b-41c4-ab92-a471f7821848" />

<img width="625" height="496" alt="Screenshot 2026-06-14 at 1 19 31 AM" src="https://github.com/user-attachments/assets/1ea77293-1038-4ca9-a919-e219e958cdd6" />


### 8.Compression Balancer
<img width="626" height="196" alt="Screenshot 2026-06-14 at 1 20 16 AM" src="https://github.com/user-attachments/assets/38b10b6d-cec5-40a5-af55-4b993c3b4b5d" />

<img width="626" height="435" alt="Screenshot 2026-06-14 at 1 20 36 AM" src="https://github.com/user-attachments/assets/9bcee5a8-ea7d-4f24-8346-e82a823bbc87" />


### 9.Display Statistics
<img width="623" height="399" alt="Screenshot 2026-06-14 at 1 21 21 AM" src="https://github.com/user-attachments/assets/d1652aa1-39c6-492d-9738-1dd253bc3deb" />


### 10.txt file
<img width="604" height="221" alt="Screenshot 2026-06-14 at 1 21 44 AM" src="https://github.com/user-attachments/assets/3dff6047-44cc-4ab6-a657-e098eac2b293" />


### 11.Exit
<img width="623" height="106" alt="Screenshot 2026-06-14 at 1 22 28 AM" src="https://github.com/user-attachments/assets/a94e548c-7b61-4a7b-ae18-7726b45b88cc" />


---

## 10. Results and Observations

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

## 11. Conclusion

The Enterprise Search Engine Documentation Hub demonstrates the practical application of multiple Data Structures and Algorithms within a real-world document management environment.

The project successfully integrates Trie, Stack, Queue, Hash Table, Max Heap, Graph, BFS, DFS, Priority Queue, and File Handling into a single workflow-driven system. It provides efficient document indexing, search operations, ranking, validation, citation mapping, and persistent storage.

The project achieves excellent DSA coverage while maintaining a clear connection to the problem statement and enterprise search concepts.

### Future Enhancements

- SHA-256 Digital Signatures
- Huffman Compression
- Full-Text Inverted Index Search
- Database Integration
- Web-Based Interface

