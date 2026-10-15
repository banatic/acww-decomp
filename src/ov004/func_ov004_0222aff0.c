/* func_ov004_0222aff0 @ 0x0222aff0, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *data_020ccf94;
extern int func_02073908(char *g, int a);
extern int func_02008258(void *self, int a);
extern int func_02051e28(void);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern int func_ov004_0222af6c(int self, int b, int c, int d, int e, int f, short g);

void func_ov004_0222aff0(char *self)
{
    char *q;

    q = self + 0x7d4;
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        return;
    }
    switch (func_02051e28()) {
        case 0:
            return;
        case 1:
            break;
        case 2:
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            func_0200d4e8(self, 3, 1, -1);
            return;
    }
    if (*(short *) (q + 8) == *(short *) (self + 0x8e)) {
        func_ov004_0222af6c((int) self, *(unsigned char *) (q + 0xa), *(int *) q, *(int *) (q + 4),
                            *(unsigned char *) (q + 0xb), 6, -1);
    }
}
