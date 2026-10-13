/* func_ov074_02279014 @ 0x02279014, 0x5c bytes, Thumb, module ov074
 * mwccarm 1.2/base -O1,s
 */

struct S_ov074 {
    unsigned char pad_00[0x40];
    void *unk_40;
};

extern int func_0206fc6c(void *);
extern int func_020984e8(int);
extern void *func_0207e0c4(int, int, int);
extern void func_020881fc(char *, void *);
extern void func_02088214(char *, int);
#pragma arm
extern int func_020644cc(int);
#pragma thumb
extern void func_0202ea80(int, int);
extern void func_0206844c(void *, void *, void *);
extern char data_021f3278;
extern char data_ov074_02279d14[];

void func_ov074_02279014(struct S_ov074 *self)
{
    char c;
    char *base;
    void *field;
    int r0;

    r0 = func_0206fc6c(self);
    if (r0) {
        field = self->unk_40;
        base = &data_021f3278;
        func_020881fc(base, func_0207e0c4(func_020984e8(r0), 0, 0));
        func_02088214(base, 3);
        c = (char) (func_020644cc(3) + 5);
        func_0202ea80(0x2b, 1);
        func_0206844c(field, &c, data_ov074_02279d14);
    }
}
