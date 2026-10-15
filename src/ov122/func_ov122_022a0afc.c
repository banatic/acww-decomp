/* func_ov122_022a0afc @ 0x022a0afc, 0xe8 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// The guard chain keeps a final dead compare, as in the original.

extern int func_ov002_02208014(void);
extern u8 func_ov002_02208008(void *);
extern int func_ov002_02207fe4(void *);
extern int func_ov095_02299a00(void *);
extern int func_ov095_02299a54(void *, int);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a254(void *);
extern void func_ov002_0220a314(void *);
extern unsigned char *func_ov122_022a0054(void *);
extern int func_ov122_0229efe8(void *, int);
extern void func_ov122_0229f250(void *);
extern int func_ov122_022a024c(void *);
extern int func_ov122_022a0204(void *);
extern int func_ov122_022a0168(void *);
extern int func_ov122_022a0098(void *);
extern int func_ov122_022a00fc(void *);
extern int func_ov122_022a006c(void *);

void func_ov122_022a0afc(void *o)
{
    u8 f;

    if (func_ov002_02208014() != 0) {
        func_ov122_022a0054(o);
        return;
    }
    f = func_ov002_02208008(o);
    if (func_ov122_0229efe8(o, 0x10) == 1) {
        if (func_ov095_02299a00((char *) o + 0xc0) == 0x104) {
            if (func_ov002_02207fe4(o) != 0) {
                f = f & ~0x20;
            }
        }
    }
    switch (func_ov095_02299a54((char *) o + 0xc0, f)) {
        case 1:
            func_ov002_0220a2b4((char *) o + 0x4058);
            func_ov122_0229f250(o);
            break;
        case 2:
            func_ov002_0220a254((char *) o + 0x4058);
            func_ov122_0229f250(o);
            break;
        case 3:
            func_ov002_0220a314((char *) o + 0x4058);
            func_ov122_0229f250(o);
            break;
        case 0:
        default:
            if (func_ov122_022a024c(o) != 0) {
                return;
            }
            if (func_ov122_022a0204(o) != 0) {
                return;
            }
            if (func_ov122_022a0168(o) != 0) {
                return;
            }
            if (func_ov122_022a0098(o) != 0) {
                return;
            }
            if (func_ov122_022a00fc(o) != 0) {
                return;
            }
            if (func_ov122_022a006c(o) != 0) {
                return;
            }
            break;
    }
}
