/* process_6: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ee7f0 @ 0x020ee7f0, 0x44 bytes, ARM
 * func_020ee7a4 @ 0x020ee7a4, 0x4c bytes, ARM
 */

typedef struct Node {
    unsigned char pad_00[4];
    struct Node *next;
    struct Key *key;
} Node;

typedef struct Key {
    unsigned char pad_00[4];
    int id;
} Key;

typedef struct Node_020ee7a4 Node_020ee7a4;

typedef struct UnkStruct_020ee7a4 UnkStruct_020ee7a4;

typedef struct Header Header;

struct UnkStruct_020ee7a4 {
    char pad_00[12];
    unsigned short key;
};

struct Node_020ee7a4 {
    int unk_00;
    Node_020ee7a4 *next;
    UnkStruct_020ee7a4 *info;
};

struct Header {
    Node_020ee7a4 *first;
};

Node *func_020ee7f0(Node **head, int id)
{
    Node *n;
    unsigned int miss;

    n = *head;
    if (n != 0) {
        do {
            miss = (n->key->id != id);
            if (miss == 0) {
                return n;
            }
            n = n->next;
        } while (n != 0);
    }
    return 0;
}

Node_020ee7a4 *func_020ee7a4(Header *head, int key, Node_020ee7a4 *prev)
{
    Node_020ee7a4 *node = prev ? prev->next : head->first;
    while (node) {
        unsigned int notfound = (node->info->key == key) ? 0 : 1;
        if (notfound == 0) {
            return node;
        }
        node = node->next;
    }
    return 0;
}
