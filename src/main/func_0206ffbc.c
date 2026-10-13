/* func_0206ffbc @ 0x0206ffbc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021cfccc[];

int func_0206ffbc(int x)
{
    int result = 1;
    int bit = 1 << (x & 31);
    if ((bit & data_021cfccc[x >> 5]) == 0) {
        result = 0;
    }
    return result;
}
