/* sound_melody_9: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f7054 @ 0x020f7054, 0x60 bytes, ARM
 * func_020f6ff4 @ 0x020f6ff4, 0x60 bytes, ARM
 */

#include "types.h"

typedef struct {
    void *link;
    unsigned int data;
    unsigned short id;
    unsigned char flag;
} EnvObj;

typedef struct UnkStruct_020f6ff4 {
    u32 unk_00;
    u32 unk_04;
    u16 unk_08;
    u8 unk_0A;
} UnkStruct_020f6ff4;

extern void func_020f6f3c(void *list);
extern int func_020eed18(void *obj, int param);
extern int func_020eedb8(int param, unsigned short value, void *obj);

int func_020f7054(EnvObj *self, unsigned short id, unsigned int data)
{
    unsigned int has_link;

    func_020f6f3c(&self->link);
    has_link = (self->link != 0) ? 1u : 0u;
    if (has_link > 0) {
        func_020eed18(self, 0);
    }
    self->id = id;
    self->data = data;
    self->flag = 1;
    return func_020eedb8(0, self->id, self);
}

void func_020f6ff4(UnkStruct_020f6ff4 *self, u32 arg2)
{
    u32 flag;

    func_020f6f3c((void *) self);
    flag = (self->unk_00 != 0);
    if (flag != 0) {
        func_020eed18((void *) self, 0);
    }
    self->unk_04 = arg2;
    self->unk_0A = 1;
    func_020eedb8(0, (u16) self->unk_08, (void *) self);
}
