/* func_ov004_02233f4c @ 0x02233f4c, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
extern int func_02055324(void *, void *, int);
extern char *func_0206223c(int, int);
extern void *func_020552ec(void *, const char *);
extern char data_ov004_02255c1c;

int func_ov004_02233f4c(char *self)
{
    int r = 0;
    void *table = &data_ov004_02255c1c;
    if (func_02055324(self + 0x174, table, 0) != 0) {
        int i;
        i = 0;
        do {
            *(void **) (self + 0x50 + i * 4) = func_020552ec(self + 0x174, func_0206223c(i, 0));
            i++;
        } while (i < 0x49);
        r = 1;
    }
    return r;
}
