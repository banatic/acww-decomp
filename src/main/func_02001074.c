/* func_02001074 @ 0x02001074, 0x4c bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *OS_AllocFromArenaHi(int, int, int);
extern void func_020010c0(int, int, void *);

int func_02001074(void)
{
    void *p;
    unsigned char c;

    p = OS_AllocFromArenaHi(0, 1, 0x20);
    func_020010c0(0x1d, 1, p);
    c = *(unsigned char *) p;
    if (c == 0xff) {
        return 0;
    }
    return (c & 0x50) != 0;
}
