/* func_020f4d00 @ 0x020f4d00, 0x4c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned int MIi_ReadWordStreamFromMemory(void *stream, unsigned int len);
extern void func_020efc38(void *stream, unsigned int len);
extern unsigned int func_020efc2c(void *stream, unsigned int val);

unsigned int func_020f4d00(void *stream, unsigned int len)
{
    unsigned int ret = MIi_ReadWordStreamFromMemory(stream, len);

    if (ret == 0) {
        return ret;
    }

    do {
        if (ret == len) {
            func_020efc38(stream, len);
        }
        ret = func_020efc2c(stream, ret);
    } while (ret != 0);

    return ret;
}
