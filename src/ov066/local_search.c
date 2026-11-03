/* local_search: 3 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02266cc8 @ 0x02266cc8, 0x20 bytes, ARM
 * func_ov066_02266c8c @ 0x02266c8c, 0x3c bytes, ARM
 * func_ov066_02266c7c @ 0x02266c7c, 0x10 bytes, ARM
 */

unsigned char func_ov066_02266cc8(void *arg0)
{
    unsigned char result;
    unsigned short value;

    if (arg0 != 0) {
        value = *(unsigned short *) ((char *) arg0 + 0x5c);
        if (value != 0) {
            result = *(unsigned char *) ((char *) arg0 + 0x77);
            return result;
        }
    }
    return 0;
}

void *func_ov066_02266c8c(void *ptr)
{
    if (ptr != 0 && *(unsigned short *) ((char *) ptr + 0x5c) != 0 && (int) func_ov066_02266cc8(ptr) != 0) {
        return (char *) ((int) ((char *) ptr + 0x70) + 8);
    }
    return 0;
}

extern unsigned short func_ov066_02266c7c(unsigned short *p)
{
    if (p) {
        return *p;
    }
    return 0;
}
