/* func_02026584 @ 0x02026584, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02026584;
extern void func_0209e474(struct UnkStruct_02026584 *s);
extern void (*data_020c8f10[])(unsigned short *out, struct UnkStruct_02026584 *s);

struct UnkStruct_02026584 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

void func_02026584(unsigned short *out, int unused, unsigned int index)
{
    struct UnkStruct_02026584 s;
    void (*func)(unsigned short *, struct UnkStruct_02026584 *);

    if (index < 5) {
        func = data_020c8f10[index];
        if (func != 0) {
            s.unk_00 = 0;
            s.unk_04 = 0;
            func_0209e474(&s);
            func(out, &s);
            return;
        }
    }
    *out = 0xfff1;
}
