/* unit_type_info_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02031d10 @ 0x02031d10, 0x18 bytes, Thumb
 * func_02031cf8 @ 0x02031cf8, 0x18 bytes, Thumb
 * func_02031ce0 @ 0x02031ce0, 0x18 bytes, Thumb
 * func_02031cc8 @ 0x02031cc8, 0x18 bytes, Thumb
 */

extern unsigned char data_020c908f[];
extern unsigned char data_020c908e[];
extern unsigned char data_020c908d[];
extern unsigned char data_020c908c[];

int func_02031d10(int r0)
{
    if (r0 < 0x7c) {
        return data_020c908f[r0 * 30];
    }
    return 0;
}

unsigned char func_02031cf8(int x)
{
    if (x < 124) {
        return data_020c908e[x * 30];
    }
    return 0;
}

int func_02031ce0(int r0)
{
    if (r0 < 0x7c) {
        return data_020c908d[r0 * 0x1e];
    }
    return 0;
}

unsigned char func_02031cc8(int r0)
{
    if (r0 < 0x7c) {
        return data_020c908c[r0 * 30];
    }
    return 0;
}
