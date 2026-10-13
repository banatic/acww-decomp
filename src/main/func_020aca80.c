/* func_020aca80 @ 0x020aca80, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aca80(void *arg0);

int func_020aca80(void *arg0)
{
    int val;
    int val2;

    val = *(int *) ((char *) arg0 + 0xc);
    val2 = val - 0x1000;
    val2 = val2 << 5;
    val2 = -val2;
    return val2 >> 0xc;
}
