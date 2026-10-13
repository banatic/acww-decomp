/* func_02036bbc @ 0x02036bbc, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x10];
    unsigned short unk_10;
} UnkStruct_02036bbc;

extern void func_02036a94(UnkStruct_02036bbc *p);
extern void func_02036b34(UnkStruct_02036bbc *p, int n);

void func_02036bbc(UnkStruct_02036bbc *p, int flag)
{
    if (flag != 0) {
        if (p->unk_10 != 0x30) {
            func_02036a94(p);
            func_02036b34(p, 0x30);
        }
    } else {
        func_02036a94(p);
    }
}
