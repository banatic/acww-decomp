/* func_02063f18 @ 0x02063f18, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_020640e0(int);

int func_02063f18(int arg0, unsigned char arg1)
{
    unsigned char *p;
    unsigned int i;
    p = func_020640e0(arg0);
    for (i = 0; i < 3; i++) {
        if (arg1 == p[i]) {
            return i + 1;
        }
    }
    return 1;
}
