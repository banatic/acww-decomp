/* func_020aa83c @ 0x020aa83c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020aa83c {
    char pad_00[8];
    int unk_08;
    char pad_0C[40];
    int unk_34;
};

extern int func_020ab504(int);
extern int func_020a7e50(void);
extern int func_020aa9fc(struct UnkStruct_020aa83c *);
extern int func_020a7e44(void);
extern int func_020aa9c8(struct UnkStruct_020aa83c *);
extern void func_020ab3a8(int, int);

void func_020aa83c(struct UnkStruct_020aa83c *p)
{
    if (p->unk_34 == 0) {
        return;
    }
    if (func_020ab504(p->unk_34) >= 0) {
        return;
    }
    if (func_020a7e50() != 0 && func_020aa9fc(p) != 0) {
        goto final;
    }
    if (func_020a7e44() == 0) {
        return;
    }
    if (func_020aa9c8(p) == 0) {
        return;
    }
final:
    func_020ab3a8(p->unk_34, p->unk_08);
}
