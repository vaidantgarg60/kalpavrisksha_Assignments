LRU Cache Implementation
using HashMap and Queue

Modern operating systems and databases frequently use caching
mechanisms to improve performance. One popular strategy is the Least
Recently Used (LRU) cache replacement policy, where the cache evicts the
item that has not been accessed for the longest time.

Your task is to design and implement an LRU Cache using the following data
structures:
 ->HashMap (for O(1) access to nodes)
 ->Queue implemented using your own linked list (to maintain order of usage
  — most recently used at one end, least recently used at the other)
  
You must build the queue using struct-based nodes (no library queues).

Objective

Create an LRU Cache that supports the following operations in O(1) time:
1. get(key) → returns value if key exists in cache; otherwise returns null
2. put(key, value) → inserts/updates the value; if the cache exceeds capacity,
evict the least recently used item

Requirements

1.Data Structures

a.HashMap
->Maps key to corresponding queue node
->Enables O(1) lookup of a node in the queue

b.Queue (Doubly Linked List)
->Each node must store:
Integer key
LRU Cache Implementation using HashMap and Queue 1
String data

The queue maintains usage:
->Front (Head) → Most Recently Used (MRU)
->Rear (Tail) → Least Recently Used (LRU)

2. Tasks
   
Implement the following:
createCache(int capacity)  Initialize the LRU cache with positive size  capacity .
string get(int key)  Return the value of the  key  if the key exists, otherwise
return  null .

void put(int key, string value)  Update the value of the  key  if the  key  exists.
Otherwise, add the  key-value  pair to the cache. If the number of keys
exceeds the  capacity  from this operation, evict the least recently used key.
The functions  get  and  put  must each run in  O(1)  average time complexity.

4. Constraints
1 ≤ capacity ≤ 1000
Keys are integers and values are strings
All operations must run in O(1)

6. Input Format
createCache <size>
put <key> <data>
get <key>

7. Output Format
Print the data found for the get command
Print null if not found

9. Example Test Case
LRU Cache Implementation using HashMap and Queue 2

Input:
createCache 5
put 101 token_A12
put 102 token_B93
put 103 token_C44
get 101
put 104 token_D11
put 105 token_E77
get 102
put 106 token_F88
get 103
get 104
get 101
put 107 token_G29
get 105
get 106
get 107
put 108 token_H55
put 109 token_J33
get 104
get 106
get 108
get 110
exit

Output:
token_A12
NULL
NULL
token_D11
token_A12
NULL
token_F88
token_G29
NULL
NULL
token_H55
NULL


11. Assignment Submission Guidelines
1. GitHub Repository Setup
• Create a public GitHub repository (accessible by mentors) for submitting
Kalpavriksha assignments throughout the program.
• Create a separate branch for assignment submission and raise a Pull
Request (PR)
for this branch.
2. Submission Deadline
• The assignments should be done in C language.
• The final submission deadline is 24th November, 05:00 PM.
• Late submissions will not be accepted under any circumstances.
• Any commits made to the repository after 24th November, 05:00 PM will
be
disregarded.
3. Prohibited AI Usage
• The use of AI or automated tools to complete the assignment is strictly
prohibited.
• Assignments should be completed independently.
4. Assignment Review and Compliance
• Mentors will thoroughly review each assignment submission.
LRU Cache Implementation using HashMap and Queue 4
