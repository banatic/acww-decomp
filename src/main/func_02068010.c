/* func_02068010 @ 0x02068010, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b44d4(void *p, int x, int y);

void *func_02068010(char *p)
{
    func_020b44d4(p + 0x1b54, *(int *) (p + 0x1a6c), 0);
    return p + 0x1b54;
}
