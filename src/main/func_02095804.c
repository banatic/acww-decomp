/* func_02095804 @ 0x02095804, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02095804; // unused

struct UnkStruct_02095804 {
    unsigned char pad_00[0x7f0];
    unsigned int unk_7F0;
    unsigned char pad_7F4[8];
    unsigned int unk_7FC;
};

extern struct UnkStruct_02095804 *func_02096718(int arg);
extern unsigned int func_02008258(struct UnkStruct_02095804 *ptr, unsigned int val);
extern int func_0200c1b8(struct UnkStruct_02095804 *ptr, int a, int b);

int func_02095804(void)
{
    struct UnkStruct_02095804 *p = func_02096718(4);
    if (p != 0) {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        return func_0200c1b8(p, 5, -1);
    } else {
        return 0;
    }
}
