Project has four to five command line arguments; the first is the name of the input file with all the words that you want to add to the hash table.  
Second is the query file of all the words that you want to search for to see if they're in the hash table.  The third argument is the size of the hash table, as in the number of buckets.  
The fourth argument is the Collision strategy.  The collision strategy argument is a two lower case letter abbreviation “lp” for linear Probing “qp” for quadratic probing and “dh” for double hashing. 
If double hashing is the chosen collision strategy, an extra fifth command line argument is needed which is an integer that will be used in the second hash function.


This hashtable is meant only to add alphabetical words. The program can still  separate the words and alphabetical input from non alphabetical input in the input file. 
EX:  if a line in the input file was “HI%^My names*(()Josh”  Hi, My, names, and Josh would still be added to the Hashtable.

The program doesn't add duplicates to the hash; it simply stores the lines where the duplicate words appear.

The project returns the total number of words found in the input file and it also Returns the total number of unique words as well as the total number of collisions for adding the words into the hash table.

