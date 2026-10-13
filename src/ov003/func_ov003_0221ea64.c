/* func_ov003_0221ea64 @ 0x0221ea64, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_022203d0(void);

int func_ov003_0221ea64(void *param)
{
    int result;
    result = func_ov003_022203d0();
    *(unsigned short *) ((char *) param + 0x2b4) = (unsigned short) result;
    return 1;
}
