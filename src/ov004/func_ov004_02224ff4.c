/* func_ov004_02224ff4 @ 0x02224ff4, 0x128 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206fc6c(void);
extern void *func_020984e8(void);
extern int func_0206fc8c(void);
extern void *func_020996b8(void *);
extern void *func_02072ba4(void *);
extern int func_02072b64(void *, int);
extern int func_02071aa8(int a, int b, int c, int d, int e);
extern int func_0200442c(void *addr, int a, int b, int c);
extern u16 *func_02099710(void *h);
extern u16 *func_020996f8(void *h);
extern void func_02095b58(u16 *p);
extern void func_02095b40(u16 *p);
extern void func_0206844c(void *, u8 *, void *);

extern void *data_ov004_02254794;

static inline u16 first(unsigned c)
{
    if (c < 8) {
        return (u16) (c + 0x12a8);
    }
    return 0x12a8;
}
static inline u16 second(unsigned c)
{
    if (c < 8) {
        return (u16) (c + 0x1429);
    }
    return 0x1429;
}
static inline unsigned isfirst(u16 *p)
{
    unsigned flag = 0;
    u16 c = *p;
    if (c >= 0x12a8 && c <= 0x12af) {
        flag = 1;
    }
    return flag;
}
static inline unsigned issecond(u16 *p)
{
    unsigned flag = 0;
    u16 c = *p;
    if (c >= 0x1429 && c <= 0x1430) {
        flag = 1;
    }
    return flag;
}
void func_ov004_02224ff4(char *self)
{
    struct {
        u8 b0, b1;
        u16 h2, h4;
    } m;
    void *a;
    int b;
    unsigned c;
    u16 va, vb;
    u16 cur1, cur2;
    int flag;

    if (func_0206fc6c() != 0) {
        a = func_020984e8();
        b = func_0206fc8c();
        c = func_02072b64(func_02072ba4(func_020996b8(a)), b);
        func_02071aa8(9, c, 5, 0, 1);
        func_0200442c((char *) *(void **) (self + 0xb0) + 0x514, 0x50, 0x7f, 0);

        va = first(c);
        vb = second(c);

        cur1 = *func_02099710(a);
        cur2 = *func_020996f8(a);

        if (va == cur1) {
            if (isfirst(func_02099710(a)) > 0) {
                m.h2 = va;
                func_02095b58(&m.h2);
            }
        }
        if (vb == cur2) {
            if (issecond(func_020996f8(a)) > 0) {
                m.h4 = vb;
                func_02095b40(&m.h4);
            }
        }

        m.b0 = 0x19;
        func_0206844c(*(void **) (self + 0x40), &m.b0, data_ov004_02254794);
    } else {
        m.b1 = 1;
        func_0206844c(*(void **) (self + 0x40), &m.b1, data_ov004_02254794);
    }
}
