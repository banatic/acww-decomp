/* func_020622a0 @ 0x020622a0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021cb634;
extern unsigned char *func_0206e7bc(void *, int);

unsigned char func_020622a0(int param)
{
    unsigned char *ptr;

    if (param >= 0x4A) {
        goto ret3;
    }
    ptr = func_0206e7bc(&data_021cb634, param);
    if (ptr == 0) {
        goto ret3;
    }
    return ptr[0x16];
ret3:
    return 3;
}
