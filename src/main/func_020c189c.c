/* func_020c189c @ 0x020c189c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020c189c {
    char pad_00[0x654];
    void *unk_654;
};

extern struct UnkStruct_020c189c *data_021fbbe0;
extern void func_020c26b4(struct UnkStruct_020c189c *p, int arg);

void func_020c189c(void)
{
    struct UnkStruct_020c189c *p;
    p = data_021fbbe0;
    if (p != 0) {
        if (p->unk_654 != 0) {
            func_020c26b4(p, 0);
        }
    }
}
