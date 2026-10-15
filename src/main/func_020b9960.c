/* func_020b9960 @ 0x020b9960, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ce0(void *a, void *b);

extern unsigned char data_021f6ca0[];

int func_020b9960(void *arg0)
{
    void *ptr = arg0;
    if (ptr != 0) {
        ptr = (char *) ptr + 4;
    }
    return func_020e8ce0((void *) data_021f6ca0, ptr);
}
