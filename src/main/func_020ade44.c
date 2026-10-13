/* func_020ade44 @ 0x020ade44, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020adde4(int);
extern void func_020ade78(void);

void func_020ade44(unsigned short *p, int delta)
{
    int res1;
    int tmp;
    int res2;

    res1 = func_020adde4(*p);
    tmp = delta + *p;
    if (tmp >= 50000) {
        tmp = 50000;
    }
    *p = (unsigned short) tmp;
    res2 = func_020adde4(*p);
    if (res1 != res2) {
        func_020ade78();
    }
}
