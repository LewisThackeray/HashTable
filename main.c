#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

const int NUMBER_OF_SLOTS = 10; // This is the value for the Number of Slots in the Hash Table (m)
const int NUMBER_OF_ELEMENTS = 12; // This is the value for the Number of Elements in the Hash Table (n).

typedef struct Node Node; // Forward Declaration of the Node Struct allowing it to be referenced in the KeyValuePair struct before its full definition as the definition of the Node Struct utilises the KeyValuePair struct.

typedef struct KeyValuePair {char key[6]; char value[6]; struct Node* pointer;} KeyValuePair; // Defining a Key-Value Pair which will be stored in the Hash Table, as a Hash Table is a specific implementation of a Dictionary.  The Key and Value are 5 Characters and an additional character for the NULL terminator.

struct Node {int index; struct Node* nextNode; struct Node* previousNode; KeyValuePair data;}; // Defining a Node in a Linked List, used for Chaining, where the Linked List is Doubly Linked so the Node contains a Pointer to the Next Node and a Pointer to the Previous Node.

KeyValuePair createKeyValuePair() { // This function is responsible for creating a Key-Value Pair, where the Key and Value are a random sting of characters of length 5.
    const char characterSet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; KeyValuePair myKeyValuePair; int length = (sizeof(characterSet) / sizeof(characterSet[0])) - 1;
    for (int i = 0; i < 5; i++) {myKeyValuePair.key[i] = characterSet[rand() % length];} myKeyValuePair.key[5] = '\0'; for (int i = 0; i < 5; i++) {myKeyValuePair.value[i] = characterSet[rand() % length];} myKeyValuePair.value[5] = '\0'; myKeyValuePair.pointer = NULL;
    return myKeyValuePair;
}

int hashFunction(char* key) { // This function is responsible for producing a Hash Value based on the Key in the Key-Value Pair.
    // Using the djb2 Hash Function, created by Daniel J Bernstein, due its simplicity and efficiency as it consists of basic arithmetic operations and its good distribution of Keys across the Hash Table.
    unsigned long hash = 5381; int c; while ((c = *key++)) {hash = ((hash << 5) + hash) + c;} int index = (hash % NUMBER_OF_SLOTS + NUMBER_OF_SLOTS) % NUMBER_OF_SLOTS; return index;
}

void printHashTable(KeyValuePair* myHashTable) { // This function is responsible for displaying the Hash Table to the User.
    for (int i = 0; i < NUMBER_OF_SLOTS; i++) {
        if (myHashTable[i].key[0] == '\0' && myHashTable[i].value[0] == '\0' && myHashTable[i].pointer == NULL) { // If the Slot in the Hash Table is empty.
            printf("%i: \n", i); // Symbolising an Empty Slot in the Hash Table.
        } else if (myHashTable[i].key[0] == '\0' && myHashTable[i].value[0] == '\0' && myHashTable[i].pointer != NULL ) { // If the Slot in the Hash Table contains a Pointer to the Head of a Linked List.
            char linkedListSequence[1000] = ""; Node* currentNode = myHashTable[i].pointer; while (currentNode->nextNode != NULL) {
                char thisNode[200]; sprintf(thisNode, "[ Index: %i Key: %s Value: %s ] ->", currentNode->index, currentNode->data.key, currentNode->data.value); // Getting the Relevant Data for Each Node, Creating a String and Storing the String in a Buffer.
                strcat(linkedListSequence, thisNode); currentNode = currentNode -> nextNode; // Iterating to the Next Node in the Linked List.
            }
            printf("%i: {} -> %s\n", i, linkedListSequence); // Symbolising a Linked List at the Slot in the Hash Table.
        } else if (myHashTable[i].key[0] != '\0' && myHashTable[i].value[0] != '\0' && myHashTable[i].pointer == NULL) { // If the Slot in the Hash Table contains a Key-Value Pair.
            printf("%i: { Key: %s Value: %s } \n", i, myHashTable[i].key, myHashTable[i].value);
        } else {printf("ERROR: The Hash Table is in a Unrecognised Format.");}
    }
}

void DictionaryOperation_Insert(KeyValuePair* myHashTable, KeyValuePair kvPair) {
    int index = hashFunction(kvPair.key); // Get the hash index

    // If the slot is empty, insert directly
    if (myHashTable[index].key[0] == '\0' && myHashTable[index].value[0] == '\0' && myHashTable[index].pointer == NULL) {
        strcpy(myHashTable[index].key, kvPair.key);
        strcpy(myHashTable[index].value, kvPair.value);
        myHashTable[index].pointer = NULL; // No linked list yet
    } else {
        // Collision detected, need to insert into linked list
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            perror("Failed to allocate memory for new node");
            return; // Handle allocation failure
        }
        
        // Set new node's data
        strcpy(newNode->data.key, kvPair.key);
        strcpy(newNode->data.value, kvPair.value);
        newNode->nextNode = NULL;

        // If there is already a linked list at this index
        if (myHashTable[index].pointer != NULL) {
            Node* currentNode = myHashTable[index].pointer;

            // Traverse to the end of the linked list
            while (currentNode->nextNode != NULL) {
                currentNode = currentNode->nextNode;
            }
            currentNode->nextNode = newNode; // Link the new node at the end
            newNode->previousNode = currentNode; // Set the previous pointer
        } else {
            // If no linked list yet, make this node the head
            myHashTable[index].pointer = newNode;
            myHashTable[index].key[0] = '\0'; // Clear the original key
            myHashTable[index].value[0] = '\0'; // Clear the original value
        }
    }
}

// THE INSERT FUNCTION IS NOT WORKING AND NEEDS TO BE FIXED!!!

void DictionaryOperation_Insert(KeyValuePair* myHashTable, KeyValuePair kvPair) { // This function is responsible for inserting the Key-Value Pairs into the Hash Table.
    int index = hashFunction(kvPair.key); // Getting the Hash Value of the Key.
    if (myHashTable[index].key[0] == '\0' && myHashTable[index].value[0] == '\0' && (myHashTable[index].pointer == NULL)) { // Checking if the Specified Slot in the Hash Table is Empty, by Checking if the First Element in the Key or Value is a NULL Terminator.
        strcpy(myHashTable[index].key, kvPair.key); strcpy(myHashTable[index].value, kvPair.value); myHashTable[index].pointer = NULL;
    } else { // If the Slot is Not Empty, we need to Insert the Key-Value Pair as a Node in a Linked List.
        if (myHashTable[index].pointer != NULL) { // If the Pointer is not a NULL Pointer, there is already a Pointer to the Head of the Linked List at that Location.
            Node* currentNode = myHashTable[index].pointer; while (currentNode->nextNode != NULL) {currentNode = currentNode->nextNode;} // Performing a Forward Traversal on the Linked List until we reach the end.
            Node* newNode = (Node*)malloc(sizeof(Node)); strcpy(newNode->data.key, kvPair.key); strcpy(newNode->data.value, kvPair.value); newNode->index = currentNode->index + 1; // Allocating Memory for the New Node and Assigning Values.
            newNode->nextNode = NULL; newNode->previousNode = currentNode; currentNode->nextNode = newNode; // Sorting Out the Links between the Two Nodes.
        } else { // If there is a Key-Value Pair stored at the Location and not a Pointer to the Head of the Linked List.
            Node* existingNode = (Node*)malloc(sizeof(Node)); strcpy(existingNode->data.key, myHashTable[index].key); strcpy(existingNode->data.value, myHashTable[index].value); existingNode->nextNode = NULL; existingNode->previousNode = NULL; // Allocating Memory and Creating a Node for the Key-Value Pair already stored at that Slot in the Array.
            Node* newNode = (Node*)malloc(sizeof(Node)); strcpy(newNode->data.key, kvPair.key); strcpy(newNode->data.value, kvPair.value); newNode->nextNode = NULL; newNode->previousNode = existingNode; // Allocating Memory and Creating a Node for the Key-Value Pair that caused the Collision.
            existingNode->nextNode = newNode; myHashTable[index].pointer = existingNode; myHashTable[index].key[0] = '\0'; myHashTable[index].value[0] = '\0'; // Sorting Out the Links between the Two Nodes and Ensuring the Hash Table is in the Correct Format.
        }
    }
}

char* DictionaryOperation_Search(KeyValuePair* myHashTable, char* key) { // This function is responsible for searching for a Key-Value Pair in the Hash Table.
    int hashIndex = hashFunction(key); // Getting the Hash Value of the Key.
    if (myHashTable[hashIndex].key == key && myHashTable[hashIndex].pointer == NULL) {return myHashTable[hashIndex].value;} // If the Key at the Index matches the Key that we are Searching for, we Return the Key.
    else if (myHashTable[hashIndex].key[0] == '\0' && myHashTable[hashIndex].pointer != NULL) { // If there is not a Key at the Index but there is a Pointer to the Head of a Linked List, we Traverse the Linked List.
        Node* currentNode = myHashTable[hashIndex].pointer; while (currentNode->nextNode != NULL) { // Performing a Forward Traversal until the Key is Found.
            if (currentNode->data.key == key) {return myHashTable[hashIndex].value;} else {currentNode = currentNode->nextNode;} // Returning the Value in the Key-Value Pair if we find the Node.
        }
    } else {printf("ERROR: The Key provided doesn't correspond to a Key-Value Pair in the Hash Table.");} // Raising an error if the Key did not correspond to a Key-Value Pair in the Hash Table.
}

void DictionaryOperation_Delete(KeyValuePair* myHashTable, char* key) { // This function is responsible for deleting a Key-Value Pair from the Hash Table.
    int hashIndex = hashFunction(key); // Getting the Hash Value of the Key.
    if (myHashTable[hashIndex].key == key && myHashTable[hashIndex].pointer == NULL) { // If the Key at the Index matches the Key that we want to Delete.
        myHashTable[hashIndex].key[0] = '\0'; myHashTable[hashIndex].value[0] = '\0'; // Setting the First Character in the Key and Value Strings as a NULL Terminator - Deleting the Contents of the Strings.
    } else if (myHashTable[hashIndex].key[0] == '\0' && myHashTable[hashIndex].pointer != NULL) { // If there is not a Key at the Index but there is a Pointer to the Head of a Linked List, we Traverse the Linked List.
        Node* currentNode = myHashTable[hashIndex].pointer; while (currentNode->nextNode != NULL) { // Performing a Forward Traversal until the Key is Found.
            if (currentNode->data.key == key) { // If the Key-Value pair is found, we need to Delete the Node.
                Node* previousNode = currentNode->previousNode; Node* nextNode = currentNode->nextNode; previousNode->nextNode = nextNode; nextNode->previousNode = previousNode; free(currentNode); // Deleting the Node and Deallocating Memory for the Node.
            } else {currentNode = currentNode->nextNode;} // Continue Traversing the Linked List if the Key is not Found.
        }
    } else {printf("ERROR: The Key provided doesn't correspond to a Key-Value Pair in the Hash Table.");} // Raise an Error if the Node cannot be found.
}

int main() {
    srand(time(NULL)); // Seeding the Random Number Generator.
    KeyValuePair myHashTable[NUMBER_OF_SLOTS];  for (int i = 0; i < NUMBER_OF_SLOTS; i++) {myHashTable[i].key[0] = '\0'; myHashTable[i].value[0] = '\0'; myHashTable[i].pointer = NULL;} // Implementing my Hash Table as an Array where Each Slot has an Empty Key-Value Pair and a NULL Pointer.
    for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {KeyValuePair kvPair = createKeyValuePair(); DictionaryOperation_Insert(myHashTable,kvPair);}
    printHashTable(myHashTable);
    return 0;
}