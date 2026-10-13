/* func_ov004_0221e634 @ 0x0221e634, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c0e0(char *self);
extern int func_0201c040(char *self, int *p, int *q);
extern void func_0201c054(char *self, int a, int b, int c);
extern int func_0207f150(int h);
extern void func_0202dc3c(char *a, char *b, int c);
extern int func_0201c2a4(char *self, int n);
extern void func_02016108(char *a, int b);
extern void func_ov004_0221eb6c(char *a, char *b, int c);
extern int func_ov004_0221eb44(char *a, char *b);
extern int func_020a7278(void);
extern char *data_020ccf94;

int func_ov004_0221e634(int unused, char *self)
{
    // DECLS
    int p, q;
    int h;
    // ENDDECLS

    if (func_0201c0e0(self) != 0) {
        p = 4;
        q = 4;
        h = *(int *) (self + 0x830);
        if (func_0201c040(self, &p, &q) != 0 && p == *(int *) (data_020ccf94 + 0x64) && p == q) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), *(int *) (data_020ccf94 + 0x64));
            if (h != 0 && func_0207f150(h) != 3) {
                *(int *) (self + 0x8d8) = 0xc;
            } else {
                *(int *) (self + 0x8d8) = 0;
            }
            func_0202dc3c(self + 0x680, self, *(int *) (self + 0x8d8));
            func_02016108(self + 0x680, func_0201c2a4(self, 4));
            func_ov004_0221eb6c(self + 0x8a0, self, 1);
        } else if (func_020a7278() != 0 && q == 4) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), 4);
            if (func_ov004_0221eb44(self + 0x8a0, self) == 0) {
                func_ov004_0221eb6c(self + 0x8a0, self, 0);
            }
        }
    }
    return 0;
}
