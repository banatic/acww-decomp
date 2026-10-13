/* func_ov002_022081f4 @ 0x022081f4, 0x48 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022081f4 {
    char pad_00[0x64];
    char unk_64;
};
struct UnkStruct_022081f4_2 {
    char pad_00[0x34];
    unsigned short unk_34;
    char pad_36[0xe];
    unsigned short unk_44;
};

extern void func_02070204(char *arg);
extern struct UnkStruct_022081f4_2 *func_020ee45c(struct UnkStruct_022081f4 *p);
extern void func_020ee3c0(struct UnkStruct_022081f4 *p, unsigned short x);
extern void func_020ee324(struct UnkStruct_022081f4 *p, unsigned short x);
extern void func_0202f144(struct UnkStruct_022081f4 *p, int x);

void func_ov002_022081f4(struct UnkStruct_022081f4 *p, int param2)
{
    func_02070204(&p->unk_64);
    if (param2 == 2) {
        struct UnkStruct_022081f4_2 *q = func_020ee45c(p);
        if (q != 0) {
            func_020ee3c0(p, q->unk_34 + 1);
            func_020ee324(p, q->unk_44 + 1);
        }
    }
    func_0202f144(p, param2);
}
