/* func_ov140_02299fc8 @ 0x02299fc8, 0x58 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov140_0229a12c(void *self);
extern void func_020708e4(void *dst, const void *src, unsigned int size);
extern void func_02070a98(void *obj, unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e,
                          unsigned int f);
extern void func_02070a04(void *obj, unsigned int a, unsigned int b);

struct UnkStruct_02299fc8 {
    unsigned char pad_00[0x8dd];
    unsigned char unk_8DD;
};

void func_ov140_02299fc8(struct UnkStruct_02299fc8 *self)
{
    void *obj;
    unsigned short tmp[2];

    obj = func_ov140_0229a12c(self);
    tmp[0] = (unsigned short) (self->unk_8DD + 0xff10);
    tmp[1] = 0;
    func_020708e4(obj, tmp, 2);
    func_02070a98(obj, 8, 0x1f2, 1, 0xf, 0, 1);
    func_02070a04(obj, 0, 0);
}
