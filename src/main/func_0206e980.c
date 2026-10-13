/* func_0206e980 @ 0x0206e980, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cfbac;
extern int data_021cfbcc;
extern int func_02004130(int *p);

int func_0206e980(void)
{
    return (data_021cfbac != 0) || (func_02004130(&data_021cfbcc) != 0);
}
