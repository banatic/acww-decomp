/* func_020ee7f0 @ 0x020ee7f0, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
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
