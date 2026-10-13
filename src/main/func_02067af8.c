/* func_02067af8 @ 0x02067af8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a81e0(void *ptr);

void func_02067af8(void *ptr)
{
    int i;
    for (i = 0; i < 11; i++) {
        func_020a81e0((char *) ptr + 0x14b8 + i * 0x5c);
    }
}
