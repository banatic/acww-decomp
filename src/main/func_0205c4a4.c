/* func_0205c4a4 @ 0x0205c4a4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern unsigned int func_0205f800(void);
extern __arm unsigned int func_020ea0e0(unsigned int, int);
extern unsigned int data_021c9ad0;

unsigned int func_0205c4a4(int param)
{
    unsigned char count = ((unsigned char *) data_020ccf94)[0x6c];
    unsigned int size;
    unsigned int term;

    size = 0;
    term = size;
    term = term + ((func_0205f800() + 3) & ~3u);
    term = (term + 0x4b) & ~3u;
    size = size + term * count;
    return data_021c9ad0 = func_020ea0e0(size, param);
}
