/* func_0205d5f0 @ 0x0205d5f0, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned char func_020b65c4(void);
extern u32 func_020b5e04(unsigned int);
extern u32 func_020b5df8(unsigned int);
extern u32 func_02085f08(void);
extern u32 func_0203cfc0(void);
extern u32 func_020e9968(void *a, u32 b, int c);
extern void func_0205d4f0(void *p, int n);

extern void *data_021c9af4;
extern void *data_020ccf94;

void func_0205d5f0(u32 *p)
{
    void *gA = data_021c9af4;
    u32 r4 = ((u8 *) data_020ccf94)[0x6c];
    u32 r6;

    r6 = func_020b5e04((unsigned int) func_020b65c4());
    if (r4 < r6) {
        r6 = r4;
    }

    for (r4 = 0; r4 < r6; r4++) {
        p[r4] = func_020e9968(gA, func_0203cfc0(), 4);
    }
    p[4] = func_020e9968(gA, func_0203cfc0(), 4);

    if (r6 == 0) {
        r6 = 1;
    }

    r4 = func_020b5df8((unsigned int) func_020b65c4());
    r6 = r4 + func_02085f08() - r6;

    for (r4 = 5; r4 < r6 + 5; r4++) {
        p[r4] = func_020e9968(gA, func_0203cfc0(), 4);
    }

    func_0205d4f0((u8 *) p + 0x3c, 4);
}
