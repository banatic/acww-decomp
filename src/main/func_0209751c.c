/* func_0209751c @ 0x0209751c, 0xa6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(u32 *p, int n);
extern int func_0209782c(void);
extern int func_02097ad0(int);
extern int func_02098a0c(int);
extern void func_020972b4(unsigned char);
extern int func_02097d68(int, u32 *);
extern int func_02097430(u32 *);
extern void func_02097cbc(int, unsigned char);
extern void func_02097d50(int, u32 *);
extern int func_0209737c(u32 *);
extern int func_020644cc(int);
extern int func_02097300(u32 *);

void func_0209751c(u32 *p, int n)
{
    int r6;
    int r4;

    r6 = func_020984e8(p, n);
    if (r6 == 0) {
        return;
    }
    if (n < 1) {
        return;
    }

    if (func_0209782c() == 0) {
        if (func_02097ad0(-1) == 1) {
            return;
        }
    }

    r4 = func_02098a0c(r6);
    func_020972b4((unsigned char) p[1]);
    if (func_02097d68(r4, p) != 0) {
        return;
    }

    if (func_02097430(p) != 0) {
        func_02097cbc(r4, (unsigned char) p[0]);
        func_02097d50(r4, p);
        return;
    } else {
        if (func_0209737c(p) != 0) {
            func_02097d50(r4, p);
            return;
        } else {
            if (func_020644cc(0xa) < 2 && func_02097300(p) != 0) {
                func_02097d50(r4, p);
                return;
            }
            func_02097d50(r4, p);
            return;
        }
    }
}
