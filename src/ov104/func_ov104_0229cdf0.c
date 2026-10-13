/* func_ov104_0229cdf0 @ 0x0229cdf0, 0xd4 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xB8];
    unsigned char b8;
} UnkStruct_0229cdf0;

extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);
extern int func_ov104_0229da80(void *, int);
extern int func_ov104_0229c364(void *, int);
extern void func_ov002_0220a314(void *);

void func_ov104_0229cdf0(UnkStruct_0229cdf0 *a, int x, int c)
{
    int diff = a->b8 - 11;
    int half = diff >> 1;

    if (func_ov002_022088ac(x)) {
        diff &= 1;
        if (diff > 0) {
            a->b8--;
        } else {
            a->b8 = (half << 1) + 22;
            return;
        }
    } else {
        if (func_ov002_0220889c(x)) {
            diff &= 1;
            if (diff < 1) {
                a->b8++;
            }
        }
    }

    if (func_ov104_0229da80(a, a->b8) == 0) {
        return;
    }
    if (func_ov104_0229c364(a, 0x30) != 0) {
        return;
    }

    if (func_ov002_022088cc(x)) {
        if (half > 0) {
            a->b8 -= 2;
        }
        return;
    }

    if (func_ov002_022088bc(x)) {
        if (half < 4) {
            a->b8 += 2;
        } else {
            if (c != 0) {
                return;
            }
            a->b8 = 0x1f;
            func_ov002_0220a314((char *) a + 0x24a0);
        }
    }
}
