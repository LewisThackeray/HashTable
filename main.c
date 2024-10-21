#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const int NUMBER_OF_SLOTS = 10; // This is the value for the Number of Slots in the Hash Table (m)
const int NUMBER_OF_ELEMENTS = 8; // This is the value for the Number of Elements in the Hash Table (n).

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

void DictionaryOperation_Insert(KeyValuePair* myHashTable, KeyValuePair kvPair) { // This function is responsible for inserting the Key-Value Pairs into the Hash Table.
    int index = hashFunction(kvPair.key); 
    if (kvPair.key[0] == '\0' && kvPair.value[0] == '\0' && (kvPair.pointer == NULL)) { // Checking if the Specified Slot in the Hash Table is Empty, by Checking if the First Element in the Key or Value is a NULL Terminator.
        strcpy(myHashTable[index].key, kvPair.key); strcpy(myHashTable[index].value, kvPair.value); myHashTable[index].pointer = NULL;
    } else { // If the Slot is Not Empty, we need to Insert the Key-Value Pair as a Node in a Linked List.
        if (myHashTable[index].pointer != NULL) { // If the Pointer is not a NULL Pointer, there is already a Pointer to the Head of the Linked List at that Location.
            Node* currentNode = myHashTable[index].pointer; while (currentNode->nextNode != NULL) {currentNode = currentNode->nextNode;} // Performing a Forward Traversal on the Linked List until we reach the end.
            Node* newNode = (Node*)malloc(sizeof(Node)); strcpy(newNode->data.key, kvPair.key); strcpy(newNode->data.value, kvPair.value); newNode->index = currentNode->index + 1; // Allocating Memory for the New Node and Assigning Values.
            newNode->nextNode = NULL; currentNode->nextNode = newNode; newNode->previousNode = currentNode; // Sorting Out the Links between the Two Nodes.
        } else { // If there is a Key-Value Pair stored at the Location and not a Pointer to the Head of the Linked List.
            Node* existingNode = (Node*)malloc(sizeof(Node)); strcpy(existingNode->data.key, myHashTable[index].key); strcpy(existingNode->data.value, myHashTable[index].value); existingNode->index = 0; // Allocating Memory and Creating a Node for the Key-Value Pair already stored at that Slot in the Array.
            Node* newNode = (Node*)malloc(sizeof(Node)); strcpy(newNode->data.key, kvPair.key); strcpy(newNode->data.value, kvPair.value); newNode->index = 1; // Allocating Memory and Creating a Node for the Key-Value Pair that caused the Collision.
            existingNode->previousNode = NULL; existingNode->nextNode = newNode; newNode->previousNode = existingNode; newNode->nextNode = NULL; // Sorting Out the Links between the Two Nodes.
        }
    } 
}

KeyValuePair DictionaryOperation_Search() { // This function is responsible for searching for a Key-Value Pair in the Hash Table.
    // Code goes here. 
}

void DictionaryOperation_Delete() { // This function is responsible for deleting a Key-Value Pair from the Hash Table.
    // Code goes here.
}

int main() {
    srand(time(NULL)); // Seeding the Random Number Generator.
    KeyValuePair myHashTable[NUMBER_OF_SLOTS];  for (int i = 0; i < NUMBER_OF_SLOTS; i++) {myHashTable[i].key[0] = '\0'; myHashTable[i].value[0] = '\0'; myHashTable->pointer = NULL;} // Implementing my Hash Table as an Array where Each Slot has an Empty Key-Value Pair and a NULL Pointer.
    for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {KeyValuePair kvPair = createKeyValuePair(); DictionaryOperation_Insert(myHashTable,kvPair);}
    return 0;
}