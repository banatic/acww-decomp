/* func_0203c4d0 @ 0x0203c4d0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203c4d0(int *param);

int func_0203c4d0(int *param)
{
    int r1;
    int r0;
    int result;

    r1 = *(int *) ((char *) param + 0xc0);
    r0 = *(int *) ((char *) param + 0xb0);
    result = r1 + r0;
    if (result < 0) {
        result = 0;
    }
    return result;
}
