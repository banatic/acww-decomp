/* func_02018ca4 @ 0x02018ca4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164cc(void *ptr, int);
extern void func_02016764(void *a, void *b, int c, unsigned short d, int e, int f, int g, int h);
extern unsigned short data_020c80f8;

void func_02018ca4(void *param0, void *param1)
{
    if (func_020164cc((char *) param1 + 0x334, (int) param1)) {
        func_02016764((char *) param1 + 0x334, param1, 0x78, data_020c80f8, 1, 0x1000, 0, 0);
        *((unsigned char *) param0 + 0x98) = 1;
    }
}
