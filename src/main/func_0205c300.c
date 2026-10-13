/* func_0205c300 @ 0x0205c300, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020cd41c;
extern int data_020cd420;
extern unsigned int data_021c9ac0;
extern __arm unsigned int func_020ea0e0(unsigned int, int);

unsigned int func_0205c300(int param)
{
    unsigned int size = 0;
    unsigned int mask = ~(data_020cd41c - 1);
    unsigned int term;

    term = ((data_020cd420 + (data_020cd41c - 1)) & mask) + 0x48;
    term = (term + (data_020cd41c - 1)) & mask;
    size = size + (term << 3);
    return data_021c9ac0 = func_020ea0e0(size, param);
}
