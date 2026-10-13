/* func_0205da78 @ 0x0205da78, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205da78(void *arg0);

void func_0205da78(void *arg0)
{
    int i;
    int j;
    short *ptr;
    short value;

    value = 0x16f;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 2; j++) {
            ptr = (short *) ((char *) arg0 + (i * 2) + (j * 0x12) + 0x48);
            *ptr = value;
        }
    }
}
