/* func_ov004_0223c080 @ 0x0223c080, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223c080;
struct UnkStruct_0223c080_2 {
    struct UnkStruct_0223c080 *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};
extern struct UnkStruct_0223c080_2 *data_021c80bc;
extern int func_02037e0c(struct UnkStruct_0223c080 *, int, int, u8);
extern int func_0204bcdc(int);
extern int func_0204bc64(int);
extern int func_0204bc7c(int);
extern void func_ov004_0223c62c(int, int, int, int, u8, int);

static __inline int atleast(unsigned int x, unsigned int n)
{
    return x > n;
}
static __inline struct UnkStruct_0223c080 *get(void)
{
    struct UnkStruct_0223c080_2 *g = data_021c80bc;
    if (!atleast(g->unk_04, 0) || !atleast(g->unk_08, 0) || g->unk_00 == 0) {
        return 0;
    }
    return g->unk_00;
}

void func_ov004_0223c080(void *self)
{
    struct UnkStruct_0223c080 *q = get();
    u32 k;
    int i, j;
    for (k = 0; k < 2; k++) {
        for (i = 0; i < 0x10; i++) {
            for (j = 0; j < 0x10; j++) {
                int item = func_02037e0c(q, j, i, k);
                if (item != 0 && func_0204bcdc(item) != 0) {
                    int c = func_0204bc64(item);
                    int d = func_0204bc7c(item);
                    func_ov004_0223c62c(j, i, c, d, k, 0);
                }
            }
        }
    }
}
