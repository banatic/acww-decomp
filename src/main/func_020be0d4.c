/* func_020be0d4 @ 0x020be0d4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020be0d4(void *param1, int param2);

int func_020be0d4(void *param1, int param2)
{
    int r4;
    int r3;
    int r0;

    r4 = 0x3c;
    r3 = 0;
    r0 = (int) param1;

    while (r3 < 0x3c) {
        if (param2 == *(int *) r0) {
            r4 = r3;
            break;
        }
        r3++;
        r0 += 0x74;
    }

    return r4;
}
