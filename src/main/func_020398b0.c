/* func_020398b0 @ 0x020398b0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02039668(void *ptr, int index);

extern unsigned char data_021c6738[];

void func_020398b0(void)
{
    int i;
    void *ptr;

    for (i = 0; i < 4; i++) {
        ptr = *(void **) data_021c6738;
        func_02039668(ptr, i);
    }
}
