/* func_020943ac @ 0x020943ac, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d1708;
extern int data_020d1780;
extern int func_02094d48(int a, int *b, int *c);

int func_020943ac(int a)
{
    return func_02094d48(a, &data_020d1708, &data_020d1780);
}
