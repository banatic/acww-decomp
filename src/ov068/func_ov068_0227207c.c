/* func_ov068_0227207c @ 0x0227207c, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_02008258(void *, int);
extern void *func_ov068_0227200c(void *, int, int);

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0x8];
    int unk_7FC;
} UnkStruct_0227207c;

void *func_ov068_0227207c(void)
{
    UnkStruct_0227207c *p = func_02096718(4);
    if (p) {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        return func_ov068_0227200c(p, 6, -1);
    } else {
        return 0;
    }
}
