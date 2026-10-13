/* func_0205c35c @ 0x0205c35c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern u8 data_020e54a8;
extern int data_020cd418;
extern unsigned int data_021c9ac4;

extern unsigned int func_02082240(void);
extern void func_020b65c4(void);
extern unsigned int func_020b5df8(void);
extern unsigned int func_020b5e04(void);
extern unsigned int func_02085f08(void);
extern unsigned int func_020ea0e0(unsigned int, int);

unsigned int func_0205c35c(int param)
{
    unsigned int count1;
    unsigned int sum;
    unsigned int size;
    unsigned int flag;

    flag = data_020e54a8 ? 0 : 1;
    if (flag != 0) {
        count1 = func_02082240();
    } else {
        func_020b65c4();
        count1 = func_020b5df8();
        func_020b65c4();
        count1 -= func_020b5e04();
    }

    sum = count1 + func_02085f08();

    size = 0;
    {
        unsigned int term = size + ((data_020cd418 + 3) & ~3u);
        term = term * sum;
        size = size + term;
    }

    return data_021c9ac4 = func_020ea0e0(size, param);
}
