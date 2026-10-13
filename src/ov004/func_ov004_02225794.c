/* func_ov004_02225794 @ 0x02225794, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void);
extern char *data_020ccf94;
extern int func_02073dd4(void *g, int a);
extern int func_02073d90(void *g);
extern int func_0207b3dc(void *q);
extern void func_0207b410(void *q);
extern void func_0209a77c(void);
extern char data_021e5a2c;

int func_ov004_02225794(void)
{
    char *g;
    char *q;

    if (func_0202ec14() == 0) {
        return 0;
    }
    g = data_020ccf94;
    if (func_02073dd4(g, *(int *) (g + 0x64)) != 0) {
        if (func_02073d90(g) == 0) {
            q = &data_021e5a2c;
            if (func_0207b3dc(q) != -1) {
                func_0207b410(q);
                func_0209a77c();
            }
        }
    }
    return 1;
}
