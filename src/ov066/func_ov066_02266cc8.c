/* func_ov066_02266cc8 @ 0x02266cc8, 0x20 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov066_02266cc8(void *arg0);

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
