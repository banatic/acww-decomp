/* func_0209b750 @ 0x0209b750, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020535f0(unsigned short *p);

void func_0209b750(unsigned short *out, unsigned int match, unsigned int add)
{
    unsigned int i;
    unsigned int idx;
    unsigned short tmp;

    *out = 0xFFF1;
    tmp = 0xFFF1;
    i = 0;

    while (i < 0x34) {
        tmp = (i < 0x34) ? (i * 4 + 0x450C) : 0x450C;
        if (func_020535f0(&tmp) == match) {
            idx = i + add;
            *out = (idx < 0x34) ? (idx * 4 + 0x450C) : 0x450C;
            break;
        }
        i++;
    }
}
