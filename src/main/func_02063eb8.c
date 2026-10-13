/* func_02063eb8 @ 0x02063eb8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064108(unsigned char *);

void func_02063eb8(unsigned char *ptr)
{
    unsigned int i;
    for (i = 0; i < 9; i++) {
        func_02064108(ptr + i);
    }
}
