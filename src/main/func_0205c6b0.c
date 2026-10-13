/* func_0205c6b0 @ 0x0205c6b0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern unsigned int func_0205d208(void);
extern __arm unsigned int func_020ea0e0(unsigned int, int);
extern unsigned int data_021c9ae8;

unsigned int func_0205c6b0(int param)
{
    unsigned char count = ((unsigned char *) data_020ccf94)[0x6c];
    unsigned int size;
    unsigned int term;

    size = 0;
    term = size;
    term = term + ((func_0205d208() + 3) & ~3u);
    size = size + term * count;
    return data_021c9ae8 = func_020ea0e0(size, param);
}
