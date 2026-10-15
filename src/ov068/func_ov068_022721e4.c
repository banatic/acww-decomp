/* func_ov068_022721e4 @ 0x022721e4, 0x24 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02272044(void);

int func_ov068_022721e4(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    p[0x2da] = 0x1e;
    if (func_ov068_02272044() != 0) {
        return 1;
    }
    return 0;
}
