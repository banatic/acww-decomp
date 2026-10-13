/* func_0205c2a0 @ 0x0205c2a0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02085f08(void);
extern int data_020cd410;
extern int data_020cd414;
extern unsigned int data_021c9abc;
extern __arm unsigned int func_020ea0e0(unsigned int, int);

unsigned int func_0205c2a0(int param)
{
    int count = func_02085f08();
    unsigned int size = 0;
    unsigned int mask = ~(data_020cd410 - 1);
    unsigned int term;

    term = ((data_020cd414 + (data_020cd410 - 1)) & mask) + 0x48;
    term = (term + (data_020cd410 - 1)) & mask;
    size = size + term * count;
    return data_021c9abc = func_020ea0e0(size, param);
}
