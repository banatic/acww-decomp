/* func_02038208 @ 0x02038208, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02038208 {
    char pad_00[0xbc];
    int unk_BC;
    char pad_C0[8];
    char unk_C8;
};

extern void func_0203864c(struct UnkStruct_02038208 *);
extern void func_020383c4(struct UnkStruct_02038208 *);

void func_02038208(struct UnkStruct_02038208 *p)
{
    p->unk_BC = 3;
    p->unk_C8 = 0;
    func_0203864c(p);
    func_020383c4(p);
}
