/* func_0209d11c @ 0x0209d11c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209d11c {
    char pad_00[0x34];
    char unk_34;
    char pad_35[3];
    int unk_38;
};

extern void *func_02055b00(struct UnkStruct_0209d11c *p);

struct UnkStruct_0209d11c *func_0209d11c(struct UnkStruct_0209d11c *p)
{
    func_02055b00(p);
    p->unk_34 = 0;
    p->unk_38 = 0;
    return p;
}
