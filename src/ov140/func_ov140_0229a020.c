/* func_ov140_0229a020 @ 0x0229a020, 0x58 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov140_0229a12c(void *);
extern void func_020708e4(void *, void *, int);
extern void func_02070a98(void *, int, int, int, int, int, int);
extern void func_02070a04(void *, int, int);

struct self_0229a020 {
    unsigned char pad_00[0x8de];
    unsigned char unk_8DE;
};

void func_ov140_0229a020(struct self_0229a020 *self)
{
    void *p;
    unsigned short buf[2];

    p = func_ov140_0229a12c(self);
    buf[0] = self->unk_8DE + 0xff10;
    buf[1] = 0;
    func_020708e4(p, buf, 2);
    func_02070a98(p, 8, 0x1f3, 1, 15, 0, 1);
    func_02070a04(p, 0, 0);
}
