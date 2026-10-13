/* func_020918d8 @ 0x020918d8, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct CmdId {
    u8 b[4];
} CmdId;

typedef struct Node Node;

typedef struct SomeVec {
    int unk_00;
    int x;
    int y;
    int z;
} SomeVec;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    Node *list;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    SomeVec **vecs;
    u32 unk_1C;
    int x;
    int y;
    int z;
} UnkStruct_020918d8;

typedef struct {
    u32 unk_00;
    CmdId cmd;
    u32 unk_08;
    UnkStruct_020918d8 *obj;
} UnkStruct_020918d8_2;

typedef struct CmdEntry {
    u32 a;
    u32 b;
    u32 c;
    u16 unk_0C;
    s16 flagE;
    u16 unk_10;
    u16 unk_12;
    int unk_14;
    u32 tail18;
} CmdEntry;

struct Node {
    struct Node *next;
    u8 pad_04[0x20];
    u16 src;
    u16 dst;
};

extern CmdEntry data_021d52d8[];
extern void func_020914dc(CmdEntry *entry);

int func_020918d8(UnkStruct_020918d8_2 *self)
{
    CmdId cmd = self->cmd;
    CmdEntry *entry = &data_021d52d8[cmd.b[0]];
    int success = 0;

    if (entry->unk_14 != -1 && entry->flagE == -1) {
        UnkStruct_020918d8 *obj = self->obj;
        obj->x = entry->a + (*obj->vecs)->x;
        obj->y = entry->b + (*obj->vecs)->y;
        obj->z = entry->c + (*obj->vecs)->z;
        success = 1;
    }

    if (!success) {
        Node *node = self->obj->list;
        while (node != 0) {
            node->dst = node->src;
            node = node->next;
        }
        func_020914dc(entry);
    }

    return success;
}
