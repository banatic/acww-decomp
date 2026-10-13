/* func_ov100_0229c6dc @ 0x0229c6dc, 0x7c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2921];
    unsigned char b;
} UnkStruct_0229c6dc;

extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088bc(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088ac(void *p);
extern void func_ov100_0229c2b0(UnkStruct_0229c6dc *p, int val);

void func_ov100_0229c6dc(UnkStruct_0229c6dc *r5, void *r4)
{
    if (func_ov002_022088cc(r4)) {
        r5->b = 0x1e;
    } else if (func_ov002_022088bc(r4)) {
        r5->b = 0x1f;
    }

    if (func_ov002_0220889c(r4)) {
        if (r5->b == 0x1e) {
            r5->b = 0x19;
        } else {
            r5->b = 0x00;
        }
        func_ov100_0229c2b0(r5, 0x20);
    } else if (func_ov002_022088ac(r4)) {
        if (r5->b == 0x1e) {
            r5->b = 0x1d;
        } else {
            r5->b = 0x04;
        }
    }
}
