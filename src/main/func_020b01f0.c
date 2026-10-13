/* func_020b01f0 @ 0x020b01f0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b01f0(void *param);

int func_020b01f0(void *param)
{
    unsigned char r1;
    unsigned char r0;
    r1 = *(unsigned char *) ((char *) param + 1);
    r0 = *(unsigned char *) param;
    if (r1 < r0) {
        return 0;
    }
    return 1;
}
