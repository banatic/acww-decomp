/* func_ov068_0226bb3c @ 0x0226bb3c, 0xe0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0226cfd4(void *);
extern void func_ov068_02266c34(void *a, void *b, int c, int d, int e, void *f, int g, int h, int i);
extern void func_02019c6c(void *, int, unsigned short);
extern void func_02013c04(void *);
extern int func_02013894(void *);
extern void func_020138a4(void *, int);
extern void func_ov068_0226c964(void *, int, void *);
extern void func_0201cbbc(void *);

extern unsigned int data_020c814c;
extern unsigned short data_020c80f8;
extern unsigned int data_0213dd98[2];

extern unsigned char data_021fbee8[];

int func_ov068_0226bb3c(void *self, void *other)
{
    int zero = 0;
    unsigned long long tmp;

    func_ov068_0226cfd4(other);
    func_ov068_02266c34((char *) other + 0x898, other, zero, zero, zero, (void *) data_021fbee8, 4, data_020c814c, 1);
    func_02019c6c((char *) other + 0x564, 1, data_020c80f8);
    *(unsigned int *) ((char *) self + 0x20) = 0;

    tmp = *(unsigned long long *) &data_0213dd98;
    *(unsigned int *) ((char *) other + 0x8b0) = (unsigned int) tmp;
    *(unsigned int *) ((char *) other + 0x8b4) = (unsigned int) (tmp >> 32);

    func_02013c04((char *) other + 0x558);
    *(unsigned short *) ((char *) self + 0xda) = 0;
    *(unsigned int *) ((char *) self + 0xf8) = 0x384;

    if (func_02013894((char *) self + 0x3c) != 0) {
        self = (void *) ((char *) self + 0x3c);
        func_020138a4(self, 1);
    } else {
        func_ov068_0226c964(self, 1, other);
        *(short *) ((char *) self + 0xd8) = -1;
        self = (void *) ((char *) self + 0xda);
        *(unsigned short *) self = 0;
    }

    *(unsigned char *) ((char *) other + 0x9f0) = 0;
    func_0201cbbc((char *) other + 0x83c);
    return 1;
}
