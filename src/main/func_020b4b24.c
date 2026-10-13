/* func_020b4b24 @ 0x020b4b24, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b4b24(void *arg0);

int func_020b4b24(void *arg0)
{
    int val;
    int val2;
    int val3;

    val = *(int *) ((char *) arg0 + 0x3c);
    if (val > 0) {
        val2 = 1;
    } else {
        val2 = 0;
    }
    val3 = *(int *) ((char *) arg0 + 0x24) - 1;
    if ((unsigned int) val3 <= 1 && val2 == 0) {
        *(int *) ((char *) arg0 + 0x30) = *(int *) ((char *) arg0 + 4);
    }
    return val2;
}
