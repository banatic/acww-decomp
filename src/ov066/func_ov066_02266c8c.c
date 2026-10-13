/* func_ov066_02266c8c @ 0x02266c8c, 0x3c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_02266cc8(void *p);

void *func_ov066_02266c8c(void *ptr)
{
    if (ptr != 0 && *(unsigned short *) ((char *) ptr + 0x5c) != 0 && func_ov066_02266cc8(ptr) != 0) {
        return (char *) ((int) ((char *) ptr + 0x70) + 8);
    }
    return 0;
}
