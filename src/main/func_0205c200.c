/* func_0205c200 @ 0x0205c200, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern unsigned int data_021c9ab8;

extern unsigned int func_02082240(void);
extern void func_020b65c4(void);
extern unsigned int func_020b5df8(void);
extern unsigned int func_020b5e04(void);
extern unsigned int func_02085f08(void);
extern unsigned int func_02078d80(void);
extern unsigned int func_02078d78(void);
extern __arm unsigned int func_020ea0e0(unsigned int, int);

unsigned int func_0205c200(int param)
{
    unsigned int count1;
    unsigned int count2;
    unsigned int size;

    size = 0;

    {
        unsigned int cond = data_020e54a8 ? 0 : 1;

        if (cond > 0) {
            count1 = func_02082240();
        } else {
            func_020b65c4();
            count1 = func_020b5df8();
            func_020b65c4();
            count1 -= func_020b5e04();
        }
    }

    count2 = func_02085f08();

    {
        unsigned int term1 = ((((func_02078d80() + 3) & ~3u) + 0x4b) & ~3u);
        size = size + term1 * count1;
    }
    {
        unsigned int term2 = ((((func_02078d78() + 3) & ~3u) + 0x4b) & ~3u);
        size = size + term2 * count2;
    }

    if (size != 0) {
        data_021c9ab8 = func_020ea0e0(size, param);
    }

    return data_021c9ab8;
}
