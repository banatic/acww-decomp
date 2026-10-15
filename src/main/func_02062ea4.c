/* func_02062ea4 @ 0x02062ea4, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 val;
    u8 a;
    u8 b;
} UnkStruct_02062ea4;

typedef struct {
    u8 pad[8];
    UnkStruct_02062ea4 sub;
} UnkStruct_02062ea4_2;

void func_02061e2c(void *p, unsigned short *);
int func_0204bd08(void *p);
int func_02062a28(void *p);
int func_02062e78(UnkStruct_02062ea4_2 *self, int value);
int func_020629e4(void *p);
int func_020629dc(void *p);
int func_020629d4(void *p);
int func_0204bcdc(void *p);
int func_0204bc64(void *p);
int func_020537e8(int value);
int func_02053da4(int value);
int func_02053d9c(int value);
int func_02053d94(int value);

int func_02062ea4(UnkStruct_02062ea4_2 *self, unsigned short *argument1)
{
    struct {
        u32 pad;
        int local;
    } s;
    UnkStruct_02062ea4 *sub;

    func_02061e2c(&s.local, (unsigned short *) argument1);
    sub = &self->sub;

    if (func_0204bd08(&s.local) != 0) {
        func_02062e78(self, func_02062a28(&s.local));
        sub->val = func_020629e4(&s.local);
        sub->b = func_020629dc(&s.local);
        sub->a = func_020629d4(&s.local);
        return 1;
    }

    if (func_0204bcdc(&s.local) != 0) {
        int v = func_0204bc64(&s.local);

        func_02062e78(self, func_020537e8(v));
        sub->val = func_02053da4(v);
        sub->b = func_02053d9c(v);
        sub->a = func_02053d94(v);
        return 1;
    }

    return 0;
}
