/* trash_box_7: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222fad0 @ 0x0222fad0, 0x14 bytes, Thumb
 * func_ov004_0222fab0 @ 0x0222fab0, 0x20 bytes, Thumb
 * func_ov004_0222fa60 @ 0x0222fa60, 0x50 bytes, Thumb
 * func_ov004_0222fa3c @ 0x0222fa3c, 0x22 bytes, Thumb
 */

extern void func_0205510c(void *, int);
extern void func_ov004_0222c598(void *);
extern int func_ov004_0222f474(void *);
extern void *data_ov004_02258490;
extern int func_020ea990(void *a, void *b);
extern int func_020e8b4c(int a, int b);
extern int func_ov004_0222f6e8(int a, int b);

int func_ov004_0222fad0(char *self)
{
    // DECLS
    // ENDDECLS
    func_0205510c(self + 0xec, 0x0);
    return 0x1;
}

int func_ov004_0222fab0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222f474(self);
    func_ov004_0222c598(self);
    *(void **) ((char *) &data_ov004_02258490) = 0x0;
    return 0x1;
}

int func_ov004_0222fa60(void *a, void *b)
{
    if (b != 0 && func_020ea990((char *) b + 0x5c, (char *) a + 0x5c) < 0x299a &&
        func_020e8b4c((short) (*(short *) ((char *) a + 0x8e) + 0x8000), *(short *) ((char *) b + 0x8e)) < 0x1200) {
        return 1;
    }
    return 0;
}

void func_ov004_0222fa3c(int a, int b)
{
    switch (b) {
        case 0:
            func_ov004_0222f6e8(a, 1);
            break;
        case 8:
            func_ov004_0222f6e8(a, 0);
            break;
        default:
            break;
    }
}
