/* func_ov138_0229c878 @ 0x0229c878, 0x3c bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c878 {
    char pad_00[0x2c8];
    char unk_2C8;
};

extern int func_ov134_022999ac(void *p);
extern void func_ov134_02299980(void *p, int x);
extern void func_ov138_0229c564(void *p, int x);
extern void func_ov138_0229c7fc(void *p);
extern void func_ov002_02207fc0(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov138_0229c878(struct UnkStruct_0229c878 *self)
{
    int ret;
    ret = func_ov134_022999ac(&self->unk_2C8);
    func_ov134_02299980(&self->unk_2C8, ret);
    func_ov138_0229c564(self, 2);
    func_ov138_0229c7fc(self);
    func_ov002_02207fc0(self);
    func_ov002_02208098((void *) (self), 5);
}
