#include <stdlib.h>

const int NUMBER_OF_SLOTS = 10; // This is the value for the Number of Slots in the Hash Table (m).
const int NUMBER_OF_ELEMENTS = 12; // This is the value for the Number of Elements in the Hash Table (n).

typedef struct Node Node; // Forward Declaration of the Node Struct allowing it to be referenced in the KeyValuePair struct before its full definition as the definition of the Node struct utilises the KeyValuePair struct.
typedef struct KeyValuePair {char key[6]; char value[6]; struct Node* pointer;} KeyValuePair; // Defining a Key-Value Pair which will be stored in the Hash Table, as a Hash Table is a specific implementation of a Dictionary.  The Key and Value are 5 Characters and an Additional Character for the NULL Terminator.

KeyValuePair createKeyValuePair() { // This function is responsible for creating a Key-Value Pair, where the Key and Value are a random string of characters of length 5.
    const char characterSet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; KeyValuePair myKeyValuePair; int length = (sizeof(characterSet) / sizeof(characterSet[0])) - 1;
    for (int i = 0; i < 5; i++) {myKeyValuePair.key[i] = characterSet[rand() % length];} myKeyValuePair.key[5] = '\0'; for (int i = 0; i < 5; i++) {myKeyValuePair.value[i] = characterSet[rand() % length];} myKeyValuePair.value[5] = '\0'; myKeyValuePair.pointer = NULL;
    return myKeyValuePair;
}

void primaryHashFunction() {}

void secondaryHashFunction() {}

void printHashTable() {}

void DictionaryOperation_Search() {}

void DictionaryOperation_Insert() {}

void DictionaryOperation_Delete() {}

int main() {}