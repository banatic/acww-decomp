/* func_01ffcfc0 @ 0x01ffcfc0, 0x3c bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    struct Node *next;
    char pad_04[8];
    void *data;
};

struct List {
    struct Node *first;
    char pad_04[8];
    void *data;
};

void *func_01ffcfc0(struct List *self)
{
    void *result;
    struct Node *node;

    result = self->data;
    if (result != 0) {
        return result;
    }

    node = self->first;
    if (node != 0) {
        do {
            result = node->data;
            if (result != 0) {
                return result;
            }
            node = node->next;
        } while (node != 0);
    }

    return 0;
}
