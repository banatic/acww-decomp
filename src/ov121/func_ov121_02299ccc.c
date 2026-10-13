/* func_ov121_02299ccc @ 0x02299ccc, 0x44 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb1];
    unsigned char flag;
} UnkStruct_02299ccc;

extern void func_ov121_02299a3c(UnkStruct_02299ccc *self, int arg);
extern int func_ov121_02299e80(UnkStruct_02299ccc *self, int arg1, int arg2);
extern void func_ov121_02299d10(UnkStruct_02299ccc *self, int arg1, int arg2);

int func_ov121_02299ccc(UnkStruct_02299ccc *self, int arg1, int arg2)
{
    unsigned char old, new_val;
    old = self->flag;
    func_ov121_02299a3c(self, 0x60);
    if (func_ov121_02299e80(self, arg1, arg2) == 0) {
        func_ov121_02299d10(self, arg1, arg2);
    }
    new_val = self->flag;
    return old != new_val;
}
