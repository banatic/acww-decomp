/* func_0205171c @ 0x0205171c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
};

struct Node {
    unsigned int *value_ptr;
    struct Entry *entries;
    unsigned char pad_08[4];
    struct Node *next;
};

unsigned int func_0205171c(struct Node *node, unsigned int key)
{
    unsigned int result = 0;
    if (key & 0x80000000) {
        result = func_0205171c(node->next, key & 0x7fffffff);
    } else if (key < *(node->value_ptr)) {
        result = node->entries[key].unk_02;
    }
    return result;
}
