/* func_ov103_0229c4fc @ 0x0229c4fc, 0x30 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2da8];
    unsigned char flag;
} UnkStruct_0229c4fc;

extern void func_ov103_0229c6a0(UnkStruct_0229c4fc *self);
extern void func_ov002_022096d8(void *ptr, int val);
extern unsigned char *func_ov002_02208098(UnkStruct_0229c4fc *self, unsigned char value);

void func_ov103_0229c4fc(UnkStruct_0229c4fc *self)
{
    self->flag = 3;
    func_ov103_0229c6a0(self);
    func_ov002_022096d8((char *) self + 0x22d8, 0);
    func_ov002_02208098(self, 0x16);
}
