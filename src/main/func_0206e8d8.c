/* func_0206e8d8 @ 0x0206e8d8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cfbac;
extern int data_021cfbcc;
extern int data_020df2a0;
extern int func_02004138(void *);

void func_0206e8d8(void)
{
    if (data_021cfbac != 0) {
        data_021cfbac--;
    }
    data_020df2a0 = func_02004138(&data_021cfbcc);
}
