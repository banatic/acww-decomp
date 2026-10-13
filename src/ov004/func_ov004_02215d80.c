/* func_ov004_02215d80 @ 0x02215d80, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02057084();
extern void func_020570d4();
extern int func_ov004_0220e050();
extern int func_ov004_0223b314();
extern void *data_ov004_022531d8;
extern void *data_ov004_022531e0;
extern void *data_ov004_022531e8;

int func_ov004_02215d80(char *self, int a1)
{
    // DECLS
    int v1;
    int v4;
    // ENDDECLS
    if (a1 != 0x0) {
        v1 = *(int *) (self + 0x594);
        func_02057084(v1, &data_ov004_022531d8, func_ov004_0223b314(self, 0x594), 0x0, 0x0);
    } else {
        v4 = *(int *) (self + 0x594);
        func_020570d4(v4, &data_ov004_022531d8, func_ov004_0220e050(self + 0x6cc, 0x6cc), &data_ov004_022531e0,
                      &data_ov004_022531e8);
    }
    return 0x1;
}
