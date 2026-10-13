/* func_020edd74 @ 0x020edd74, 0x68 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xe];
    u8 unk_0E;
} UnkStruct_020edd74;
typedef struct Node Node;
struct Node {
    u8 pad_00[0x10];
    UnkStruct_020edd74 *unk_10;
};
typedef struct {
    void *unk_00;
    Node *unk_04;
} List;
typedef struct {
    u8 pad_00[0x14];
    List list;
} UnkStruct_020edd74_2;

extern Node *func_01ffcfc0(List *l);
extern Node *func_01ffcffc(Node *n);

int func_020edd74(UnkStruct_020edd74_2 *self)
{
    List *l;
    Node *end;
    Node *p;
    int flag;

    l = &self->list;
    end = func_01ffcfc0(l);
    p = l->unk_04;
    while (p != 0 && p != end) {
        flag = !p->unk_10->unk_0E;
        if (flag != 0) {
            return 1;
        }
        p = func_01ffcffc(p);
    }
    return 0;
}
