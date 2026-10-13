/* func_020ee7a4 @ 0x020ee7a4, 0x4c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct Node Node;
typedef struct UnkStruct_020ee7a4 UnkStruct_020ee7a4;
typedef struct Header Header;

struct UnkStruct_020ee7a4 {
    char pad_00[12];
    unsigned short key;
};

struct Node {
    int unk_00;
    Node *next;
    UnkStruct_020ee7a4 *info;
};

struct Header {
    Node *first;
};

Node *func_020ee7a4(Header *head, int key, Node *prev)
{
    Node *node = prev ? prev->next : head->first;
    while (node) {
        unsigned int notfound = (node->info->key == key) ? 0 : 1;
        if (notfound == 0) {
            return node;
        }
        node = node->next;
    }
    return 0;
}
