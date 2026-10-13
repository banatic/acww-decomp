/* func_ov003_02219cb4 @ 0x02219cb4, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02219cb4 {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x428];
    int unk_704;
};

extern int func_02096718(int);
extern void func_0200fa8c(void *, void *);
extern int func_ov003_02219e14(void *self, void *buf);

int func_ov003_02219cb4(void *self)
{
    struct UnkStruct_02219cb4 *p;
    int val;
    int tag;
    char buf[0x10];

    p = (struct UnkStruct_02219cb4 *) func_02096718(4);
    if (p != 0) {
        val = (int) ((unsigned int) (p->unk_2D8 << 4) >> 16);
        tag = p->unk_704;
        if ((tag == 0x67 && val == 5) || (tag == 0x44 && val == 8)) {
            func_0200fa8c(buf, p);
            return func_ov003_02219e14(self, buf);
        }
    }
    return 0;
}
