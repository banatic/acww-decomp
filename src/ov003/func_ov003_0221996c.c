/* func_ov003_0221996c @ 0x0221996c, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

extern void *func_02096718(int);
extern int func_0200e7f8(void *);
extern int func_ov003_0220f244(void *, unsigned char, int, int);
extern int func_0200f290(void *, int);
extern void func_0200f268(void *, int);
extern void func_02035638(int);

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
} UnkStruct_0221996c;

int func_ov003_0221996c(int a)
{
    UnkStruct_0221996c *x = (UnkStruct_0221996c *) func_02096718(4);
    int lim;
    if (x != 0) {
        lim = 5;
        if (lim <= func_0200e7f8(x)) {
            return 0;
        }
        if (x->unk_7F0 == 0x78) {
            return 0;
        }
        if (func_ov003_0220f244(x, (unsigned char) (a + 2), 7, -1) != 0) {
            if (func_0200f290(x, 0x1a) != 0) {
                func_0200f268(x, 0x1a);
                func_02035638(0x3f);
            }
            return 1;
        }
    }
    return 0;
}
