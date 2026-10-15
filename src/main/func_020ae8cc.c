/* func_020ae8cc @ 0x020ae8cc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aff84(void *a, void *b, void *c, int d);

int func_020ae8cc(unsigned char *first, unsigned char *second)
{
    return func_020aff84(second, first, first + 0x10, 6);
}
