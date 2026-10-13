/* func_0201272c @ 0x0201272c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201272c(void *arg0, void *arg1);

int func_0201272c(void *arg0, void *arg1)
{
    int val;
    int val2;
    int val3;
    int val4;

    val = *(int *) ((int) arg1 + 8);
    val2 = val >> 0x11;
    val3 = *(int *) arg1;
    val4 = val3 >> 0x11;
    if (val4 == *(int *) ((int) arg0 + 0x14) && val2 == *(int *) ((int) arg0 + 0x18)) {
        return 1;
    }
    return 0;
}
