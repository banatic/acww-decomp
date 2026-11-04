/* process_phases: 2 functions, module itcm
 * mwccarm 1.2/base -O4,s
 * func_01ffcffc @ 0x01ffcffc, 0x2c bytes, ARM
 * func_01ffcfc0 @ 0x01ffcfc0, 0x3c bytes, ARM
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

void *func_01ffcfc0(struct List *self);

int func_01ffcffc(int *p)
{
    int v;

    v = p[1];
    if (v == 0) {
        v = (int) func_01ffcfc0((struct List *) p);
    }
    return v;
}

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
