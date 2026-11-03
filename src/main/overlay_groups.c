/* overlay_groups: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206ffbc @ 0x0206ffbc, 0x2c bytes, Thumb
 * func_0206ff98 @ 0x0206ff98, 0x24 bytes, Thumb
 * func_0206ff74 @ 0x0206ff74, 0x24 bytes, Thumb
 * func_0206ff48 @ 0x0206ff48, 0x2c bytes, Thumb
 * func_0206ff24 @ 0x0206ff24, 0x24 bytes, Thumb
 * func_0206ff00 @ 0x0206ff00, 0x24 bytes, Thumb
 */

extern unsigned int data_021cfccc[];
extern unsigned int data_021cfcb4[];

int func_0206ffbc(int x)
{
    int result = 1;
    int bit = 1 << (x & 31);
    if ((bit & data_021cfccc[x >> 5]) == 0) {
        result = 0;
    }
    return result;
}

void func_0206ff98(int bit)
{
    data_021cfccc[bit >> 5] |= (1u << (bit & 0x1f));
}

void func_0206ff74(int bit)
{
    data_021cfccc[bit >> 5] &= ~(1u << (bit & 31));
}

int func_0206ff48(int param)
{
    int ret = 1;
    if (!((1 << (param & 31)) & data_021cfcb4[param >> 5])) {
        ret = 0;
    }
    return ret;
}

void func_0206ff24(int arg)
{
    data_021cfcb4[arg >> 5] |= (1u << (arg & 31));
}

void func_0206ff00(int bit)
{
    data_021cfcb4[bit >> 5] &= ~(1u << (bit & 31));
}
