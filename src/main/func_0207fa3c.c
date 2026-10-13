/* func_0207fa3c @ 0x0207fa3c, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020535f0(unsigned short *p);

int func_0207fa3c(int unused, unsigned short *p)
{
    unsigned int i;
    unsigned short local;
    int flag;

    flag = (*p >= 0x450c && *p <= 0x45db);
    if (flag) {
        unsigned int ret = func_020535f0(p);
        if (ret < 24) {
            local = 0xfff1;
            for (i = 0; i < 52; i++) {
                local = (i < 52) ? 0x450c + i * 4 : 0x450c;
                if (func_020535f0(&local) == ret) {
                    flag = (*p >= 0x450c && *p <= 0x45db);
                    return (flag ? ((*p - 0x450c) >> 2) : -1) - (int) i;
                }
            }
        }
    }
    return -1;
}
