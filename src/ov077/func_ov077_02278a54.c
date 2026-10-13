/* func_ov077_02278a54 @ 0x02278a54, 0x44 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

typedef void (*SubFunc)(void *self);

typedef struct {
    SubFunc *vtable;
} UnkStruct_02278a54;

typedef struct {
    unsigned char pad_00[0x658];
    UnkStruct_02278a54 sub;
} State;

extern int func_0201c2a4(State *self, int param);
extern void func_02016108(UnkStruct_02278a54 *sub, int value);
extern void func_ov077_02279358(State *self, int param);

void func_ov077_02278a54(State *self, int param)
{
    switch (param) {
        case 1: {
            int res;
            self->sub.vtable[2](&self->sub);
            res = func_0201c2a4(self, 4);
            func_02016108(&self->sub, res);
            func_ov077_02279358(self, 4);
            break;
        }
        case 8:
            func_ov077_02279358(self, 2);
            break;
    }
}
