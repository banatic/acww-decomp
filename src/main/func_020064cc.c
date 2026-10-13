/* func_020064cc @ 0x020064cc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c78f8[];

void func_020064cc(unsigned int *arg0, unsigned int arg1)
{
    unsigned int val;
    unsigned int val2;

    val = data_020c78f8[arg1];
    if (val == 0) {
        arg0[0x1bc] = 0;
    } else {
        arg0[0x1bc] = 0xb33;
    }
    return;
}
