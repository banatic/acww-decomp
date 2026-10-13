/* func_020a17a8 @ 0x020a17a8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021f3c3c;

int func_020a17a8(void)
{
    unsigned char *p;
    if (data_021f3c3c && (*(int *) ((char *) data_021f3c3c + 0x50) == 0x1f)) {
        p = (unsigned char *) data_021f3c3c + 0xa1;
        if (*p == 0x0f || *p == 0x14) {
            return 1;
        }
    }
    return 0;
}
