#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY 1000

typedef struct Node{
    int key;
      char value[100];
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct LRUCache{
    int capacity;
    int size;
     Node *head;
    Node *tail;
    Node *map[MAX_KEY];
} LRUCache;

Node *createNode(int key, char *value){
    Node *node = malloc(sizeof(Node));
    node->key = key;
    strcpy(node->value, value);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

LRUCache *createCache(int cap){
    if (cap < 1 || cap > MAX_KEY){
        return NULL;
    }
    LRUCache *cache = malloc(sizeof(LRUCache));
    cache->capacity = cap;
    cache->size = 0;
     cache->head = createNode(-1, "");
    cache->tail = createNode(-1, "");
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;
    for (int i = 0; i < MAX_KEY; i++){
        cache->map[i] = NULL;
    }
    return cache;
}

void deleteNode(Node *node){

    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void insertAtHead(LRUCache *cache, Node *node){
    node->next = cache->head->next;
    node->prev = cache->head;
    cache->head->next->prev = node;
    cache->head->next = node;
}

char *get(LRUCache *cache, int key){
    if (!cache || key < 0 || key >= MAX_KEY){
        return "NULL";
    }
    Node *node = cache->map[key];
    if (!node){
        return "NULL";
    }
    deleteNode(node);
    insertAtHead(cache, node);
    return node->value;
}

void put(LRUCache *cache, int key, char *value){
    if (key < 0 || key >= MAX_KEY){
        return;
    }
    Node *node = cache->map[key];
    if (node)  {
        strcpy(node->value , value);
         deleteNode(node);
        insertAtHead(cache, node);
        return;
    }
    if (cache->size == cache->capacity) {
        Node *lru = cache->tail->prev;
        deleteNode(lru);
        cache->map[ lru->key] = NULL;
        free(lru);
        cache->size--;
    }
    Node *newNode = createNode(key, value);
    insertAtHead(cache , newNode);
    cache-> map[key] = newNode;
    cache ->size++;
}
void freeCache(LRUCache *cache){
    if (!cache){
        return;
    }
    Node *curr = cache->head;
    while (curr)   {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    free(cache);
}

int main(){
    LRUCache *cache = NULL;
    char command[32];
    while (scanf("%s", command)) {
        if (strcmp(command, "createCache") == 0)  {
            int cap;
            scanf("%d", &cap);
            if (cache){
                freeCache(cache);
            }
            cache = createCache(cap);
        }
        else if (strcmp(command, "put") == 0) {
            int key;
            char value[100];
            scanf("%d %s", &key, value);
            if (cache){
                put(cache, key, value);
            }
        }
        else if (strcmp(command, "get") == 0) {
            int key;
            scanf("%d", &key);
            if (cache){
                printf("%s\n", get(cache, key));
            }
            else{
                printf("NULL\n");
            }
        }
        else if (strcmp(command, "exit") == 0)  {
            break;
        }
    }
        if (cache){
            freeCache(cache);
        }
    return 0;
}
