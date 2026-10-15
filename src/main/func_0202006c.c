/* func_0202006c @ 0x0202006c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc6c(void);
extern int func_0206fc44(void);
extern void func_02081b68(int, int, int);
extern int func_020984e8(void);
extern int func_02099870(int);
extern void func_0208016c(int, int, int, int);

void func_0202006c(int *r0)
{
    int *r5;
    int r4;
    int r1;
    int r0_2;
    int r3;

    r5 = r0;
    if (func_0206fc6c() != 0) {
        r1 = *(int *) ((char *) r5 + 0x100);
        r4 = *(int *) ((char *) r1 + 0x830);
        r0_2 = *(int *) ((char *) r5 + 0x12c);
        if (r0_2 != 0) {
            r1 = func_0206fc44();
            r0_2 = *(int *) ((char *) r5 + 0x12c);
            func_02081b68(r0_2, r1, 0xa);
        } else {
            r5 = (int *) func_0206fc44();
            r3 = func_02099870(func_020984e8());
            func_0208016c(r4, (int) r5, 0xa, r3);
        }
    }
}
