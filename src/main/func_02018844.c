/* func_02018844 @ 0x02018844, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_02019de4(unsigned char *);
extern void func_0201b1a4(unsigned char *, unsigned char *, int, int, unsigned short);
extern void func_0201b044(unsigned char *, void *);
extern void func_0201afd4(unsigned char *, void *);
extern void func_0201b350(unsigned char *, unsigned int);
extern volatile unsigned short data_020c80f8;
extern unsigned int data_020c8198[];
extern void func_02016764(unsigned char *, unsigned char *, unsigned int, unsigned short, int, int, int, int);
extern void func_02012444(unsigned int, unsigned short, int);
extern int func_0200442c(unsigned char *, int, int, int);
extern int func_02057d58(unsigned char *, unsigned int, unsigned char, unsigned int, unsigned char *, unsigned int);
extern int func_02057d0c(int, unsigned char *);
extern void func_02019af0(unsigned char *, int);
extern int data_021fbee8;

int func_02018844(unsigned char *param0, unsigned char *param1)
{
    unsigned char *r4;
    unsigned short saved;
    unsigned int fieldval;

    r4 = func_02019de4(param0);
    func_0201b1a4(param1 + 0x350, param1, 0, 0, *(unsigned short *) (r4 + 0x1c));
    func_0201b044(param1 + 0x350, &data_021fbee8);
    func_0201afd4(param1 + 0x350, &data_021fbee8);
    func_0201b350(param1 + 0x3aa, 0xfffffffe);
    saved = data_020c80f8;

    func_02016764(param1 + 0x334, param1, data_020c8198[*(unsigned int *) (r4 + 0x30)], data_020c80f8, 1, 0x1000, 0, 0);

    fieldval = *(unsigned int *) (param1 + 0x628);
    if (fieldval != 0) {
        func_02012444(fieldval, saved, 0);
    }

    func_0200442c(param1 + 0x514, 0x4f, 0x7f, 0);

    func_02057d58(r4 + 0x22, *(unsigned int *) (r4 + 0x24), *(unsigned char *) (r4 + 0x2c), *(unsigned int *) (r4 + 0x30),
                  param1, *(unsigned int *) (r4 + 0x28));

    func_02057d0c(1, param1);

    func_02019af0(param0, 0);

    if (*(unsigned int *) (r4 + 0x30) == 1) {
        param0[0x98] = 4;
    } else {
        param0[0x98] = 0;
    }

    return 1;
}
