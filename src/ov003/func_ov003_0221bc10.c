/* func_ov003_0221bc10 @ 0x0221bc10, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096174(void);
extern int func_ov003_0221bfa8(void *, int);
extern void func_0203ee08(void *, void *);

void func_ov003_0221bc10(void *p)
{
    char *q;

    if (func_02096174()) {
        if (func_ov003_0221bfa8(p, 8)) {
            q = (char *) p;
            if (p) {
                q += 0xec;
            }
            func_0203ee08(p, q);
        }
    }
}
