/* func_02071188 @ 0x02071188, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020641c8(void *p);
extern void func_02064210(void *a, void *b);
extern void func_0203d7c4(int a, void *b);
extern void *func_02098844(const char *s, int idx);
extern int func_02099a28(void);
extern void func_02066694(void *p);
extern int func_02099870(void *p);
extern void func_02066024(void *a, void *b, void *c, void *d, void *e, int f);
extern void func_02065ed0(void *a, int b, int c);
extern int func_02097a54(void *p);
extern void func_02066688(void *p);
extern void func_020641b0(void *p);

extern char data_021dc7aa[];
extern char data_021dc7bc[];
extern int data_020e17ac;
extern int data_020e17b0;
extern int data_020e17b4;

int func_02071188(void)
{
    char c8;
    u32 buf1[8];
    u32 buf2[0x40];
    int result;
    int i;

    func_020641c8(buf1);
    func_02064210(data_021dc7aa, buf1);
    func_0203d7c4(2, buf1);

    result = 0;

    for (i = 0; i < 4; i++) {
        void *p;
        int q;

        p = func_02098844(data_021dc7bc, i);
        if (p == 0) {
            continue;
        }
        if (func_02099a28() == 0) {
            continue;
        }

        func_02066694(buf2);
        c8 = 0;
        q = func_02099870(p);
        func_02066024(buf2, &c8, &data_020e17b4, &data_020e17ac, &data_020e17b0, q);
        func_02065ed0(buf2, 0x3870, 1);
        if (func_02097a54(buf2) != 0) {
            result = 1;
        }
        func_02066688(buf2);
    }

    func_020641b0(buf1);
    return result;
}
