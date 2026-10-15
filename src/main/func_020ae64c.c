/* func_020ae64c @ 0x020ae64c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ae64c {
    int unk_00;
    char unk_04;
};

extern int func_020ae470(struct UnkStruct_020ae64c *p);
extern void func_020ae564(struct UnkStruct_020ae64c *p);
extern void func_0209f100(void *p, int n);
extern int data_021dc7a8;

int func_020ae64c(struct UnkStruct_020ae64c *p)
{
    p->unk_04 = -1;
    if (func_020ae470(p) == 0) {
        p->unk_00 = 0;
    }
    func_020ae564(p);
    func_0209f100(&data_021dc7a8, 8);
    return 1;
}
