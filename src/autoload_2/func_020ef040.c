/* func_020ef040 @ 0x020ef040, 0xc0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u32 head, tail;
    u16 unk_08, count;
} FndList;

typedef struct {
    FndList list; // 0x00, 0xc bytes
    int state;    // 0x0c
    void *p1;     // 0x10
    u8 unk_14;    // 0x14
    u8 b;         // 0x15
    u8 unk_16;    // 0x16
    u8 unk_17;    // 0x17
    u8 unk_18;    // 0x18
    u8 pad_19[3]; // 0x19-0x1b
    u32 i;        // 0x1c
    void *l1;     // 0x20
    void *l2;     // 0x24
} UnkStruct_020ef040;

typedef struct {
    u8 a, b, c, d;
} Quad;

extern void OS_Terminate(void);
extern int func_020ef100(UnkStruct_020ef040 *self);
extern void func_0210b7e0(void *p);
extern void NNS_FndInitList(FndList *list, u16 zero);

int func_020ef040(UnkStruct_020ef040 *self, void *p1, u8 field14, volatile Quad q)
{
    if (self->state != 0) {
        OS_Terminate();
    }
    if (q.a == 0xff) {
        OS_Terminate();
    }

    {
        u8 t0 = q.a, t1 = q.b;
        self->b = t0;
        self->unk_16 = t1;
    }
    {
        u8 t2 = q.c, t3 = q.d;
        self->unk_17 = t2;
        self->unk_18 = t3;
    }

    if (q.d == 0) {
        if (func_020ef100(self) == 0) {
            return 0;
        }
    } else {
        self->i = 0xff;
    }

    self->p1 = p1;
    self->unk_14 = field14;
    func_0210b7e0(&self->l1);
    func_0210b7e0(&self->l2);
    NNS_FndInitList(&self->list, 0);
    self->state = 1;
    return 1;
}
