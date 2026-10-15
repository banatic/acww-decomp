/* func_ov003_02217234 @ 0x02217234, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_ov003_022172bc(void *, int, int, int);

typedef struct UnkStruct_02217234 {
    char pad_00[0x144];
    int unk_144;
    unsigned char unk_148;
    char pad_149[3];
    int unk_14C;
    int unk_150;
    int unk_154;
    int unk_158;
    int unk_15C;
    int unk_160;
} UnkStruct_02217234;

int func_ov003_02217234(UnkStruct_02217234 *self, int param1, int param2)
{
    char stack[0x1c];
    char *local2;
    int result;

    func_0200e92c(stack);
    local2 = stack + 0xc;
    func_0200e90c(stack, 0x46, param1, param2);

    if (self->unk_148 != 0) {
        func_ov003_022172bc(local2, self->unk_158, self->unk_160, 1);
    } else {
        func_ov003_022172bc(local2, self->unk_14C, self->unk_154, (self->unk_144 != 0) ? 1 : 0);
    }

    result = func_0200e894(self, stack);
    func_0200e91c(stack);
    return result;
}
