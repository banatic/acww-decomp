/* func_ov004_0222511c @ 0x0222511c, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc6c(void);
extern void *func_020984e8(void);
extern void *func_0206fc8c(void);
extern void *func_020996b8(void *);
extern int func_02072ba4(int object);
extern int func_02072b64(int, void *);
extern int func_02071d8c(int, int, int, int, int);
extern int func_0200442c(void *, int, int, int);
extern void func_0206844c(int, void *, void *);
extern void *data_ov004_02254794;

void func_ov004_0222511c(char *self)
{
    unsigned char buf[4];
    if (func_0206fc6c() != 0) {
        void *a = func_020984e8();
        void *b = func_0206fc8c();
        a = func_020996b8(a);
        func_02071d8c(9, func_02072b64(func_02072ba4((int) a), b), 5, 0, 1);
        func_0200442c(*(char **) (self + 0xb0) + 0x514, 0x50, 0x7f, 0);
        buf[0] = 0x18;
        func_0206844c(*(int *) (self + 0x40), &buf[0], data_ov004_02254794);
    } else {
        buf[1] = 1;
        func_0206844c(*(int *) (self + 0x40), &buf[1], data_ov004_02254794);
    }
}
