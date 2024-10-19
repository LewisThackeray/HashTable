#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int NUMBER_OF_SLOTS = 10; // This is the value for the Number of Slots in the Hash Table (m)
const int NUMBER_OF_ELEMENTS = 8; // This is the value for the Number of Elements in the Hash Table (n).

typedef struct KeyValuePair {char key[6]; char value[6];} KeyValuePair; // Defining a Key-Value Pair which will be stored in the Hash Table, as a Hash Table is a specific implementation of a Dictionary.  The Key and Value are 5 Characters and an additional character for the NULL terminator.

KeyValuePair createKeyValuePair() { // This function is responsible for creating a Key-Value Pair, where the Key and Value are a random sting of characters of length 5.
    const char characterSet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; KeyValuePair myKeyValuePair; int length = (sizeof(characterSet) / sizeof(characterSet[0])) - 1;
    for (int i = 0; i < 5; i++) {myKeyValuePair.key[i] = characterSet[rand() % length];} myKeyValuePair.key[5] = '\0'; for (int i = 0; i < 5; i++) {myKeyValuePair.value[i] = characterSet[rand() % length];} myKeyValuePair.value[5] = '\0'; 
    return myKeyValuePair;
}

int hashFunction(unsigned char* key) { // This function is responsible for producing a Hash Value based on the Key in the Key-Value Pair.
    // Using the djb2 Hash Function, created by Daniel J Bernstein, due its simplicity and efficiency as it consists of basic arithmetic operations and its good distribution of Keys across the Hash Table.
    unsigned long hash = 5381; int c; while ((c = *key++)) {hash = ((hash << 5) + hash) + c;} int index = (hash % NUMBER_OF_SLOTS + NUMBER_OF_SLOTS) % NUMBER_OF_SLOTS; return index;
}

void DictionaryOperation_Insert() {}

KeyValuePair DictionaryOperation_Search() {}

void DictionaryOperation_Delete() {}

int main() {
    srand(time(NULL)); // Seeding the Random Number Generator.
    KeyValuePair kv1 = createKeyValuePair(); printf("Key: %s | Value: %s\n", kv1.key, kv1.value); // Testing the createKeyValuePair Function.
    printf("%i\n", hashFunction(kv1.key));
    return 0;
}