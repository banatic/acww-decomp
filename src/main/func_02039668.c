/* func_02039668 @ 0x02039668, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Node;
struct UnkStruct_02039668;

typedef struct Node {
    unsigned char pad_00[0xc];
    void *owner;
} Node;

typedef struct UnkStruct_02039668 {
    unsigned char pad_00[0x2e4];
    Node *array1[4];
    Node *array2[4];
} UnkStruct_02039668;

extern void *func_020396dc(struct UnkStruct_02039668 *self, int param);
extern int func_02039ebc(Node *node);

void func_02039668(struct UnkStruct_02039668 *self, int param)
{
    void *key;
    int i;
    Node *node;

    if (param > 4) {
        return;
    }
    key = func_020396dc(self, param);

    for (i = 0; i < 4; i++) {
        node = self->array1[i];
        if (node != 0 && key == node->owner) {
            self->array1[i] = 0;
            break;
        }
    }

    for (i = 0; i < 4; i++) {
        node = self->array2[i];
        if (node != 0 && key == node->owner) {
            func_02039ebc(node);
            break;
        }
    }
}
