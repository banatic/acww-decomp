/* func_02070d74 @ 0x02070d74, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020535f0(unsigned short *t);
extern int func_02071298(void *a, unsigned short *t);
int func_02070d74(void *a, int b)
{
    int n = 0;
    unsigned int i;
    for (i = 0; i < 0x34; i++) {
        unsigned short id;
        id = (unsigned short) (i < 0x34 ? 0x450c + i * 4 : 0x450c);
        if (b == func_020535f0(&id)) {
            if (func_02071298(a, &id) != 0) {
                n++;
            }
        }
    }
    return n;
}
