/* func_02018d7c @ 0x02018d7c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201b354(void *);
extern void func_02019af0(void *, int);

struct UnkStruct_02018d7c {
    char pad_00[0x190];
    unsigned int unk_190;
    char pad_194[0x216];
    char unk_3AA;
};

void func_02018d7c(void *arg0, struct UnkStruct_02018d7c *arg1)
{
    if (((arg1->unk_190 << 4) >> 16) != 0) {
        return;
    }
    if (func_0201b354(&arg1->unk_3AA) != 0) {
        return;
    }
    func_02019af0(arg0, 1);
}
