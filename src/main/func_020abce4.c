/* func_020abce4 @ 0x020abce4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020abce4(void *arg0);

int func_020abce4(void *arg0)
{
    int val;

    val = *(int *) ((char *) arg0 + 0x13c);
    val = val - 1;
    if ((unsigned int) val <= 4) {
        return 1;
    }
    return 0;
}
