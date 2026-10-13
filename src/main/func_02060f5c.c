/* func_02060f5c @ 0x02060f5c, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned int func_02060e78(void *);
extern int func_02061008(int);
extern void func_0204de34(void);
extern void func_0204dde0(void);
extern void func_0209f128(void *, int);

extern unsigned char data_021dc7a8[];

void func_02060f5c(unsigned char *self)
{
    unsigned int a = (*(unsigned int *) (self + 0x15a0) << 18) >> 28;
    unsigned int b = (*(unsigned int *) (self + 0x15a0) << 22) >> 28;
    unsigned int c;

    if (b != a) {
        *(unsigned int *) (self + 0x15a0) = (*(unsigned int *) (self + 0x15a0) & 0xfffffc3f) | ((a & 0xf) << 6);
    }
    c = (*(unsigned int *) (self + 0x15a0) << 26) >> 29;
    if (c != func_02060e78(self)) {
        if (func_02061008(c) != 0) {
            *(unsigned int *) (self + 0x15a0) =
                (*(unsigned int *) (self + 0x15a0) & ~7) | (((*(unsigned int *) (self + 0x15a0) << 26) >> 29) & 7);
            *(unsigned int *) (self + 0x15a0) = (*(unsigned int *) (self + 0x15a0) & 0xffffc3ff) |
                                                ((((*(unsigned int *) (self + 0x15a0) << 14) >> 28) & 0xf) << 10);
            *(unsigned int *) (self + 0x15a0) = (*(unsigned int *) (self + 0x15a0) & 0xfffffc3f) |
                                                ((((*(unsigned int *) (self + 0x15a0) << 18) >> 28) & 0xf) << 6);
            func_0204de34();
            func_0204dde0();
            func_0209f128((void *) data_021dc7a8, 0xd);
        }
    }
}
