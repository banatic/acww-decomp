/* func_0205166c @ 0x0205166c, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02050f0c(void *);

struct UnkStruct_0205166c {
    char pad_00[0x58];
    int unk_58;
    int unk_5C;
};

void func_0205166c(struct UnkStruct_0205166c *p, int val)
{
    p->unk_5C = val;
    if (p->unk_58 == 2 && p->unk_5C != -1) {
        func_02050f0c(p);
        p->unk_5C = -1;
    }
}
