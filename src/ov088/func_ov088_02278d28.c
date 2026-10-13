/* func_ov088_02278d28 @ 0x02278d28, 0x2c bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02278d28 {
    unsigned char pad_00[0xb8];
    unsigned int unk_B8;
} UnkStruct_02278d28;

extern int func_020e8858(unsigned int);
extern void func_ov088_02278f0c(UnkStruct_02278d28 *p, int a);
extern void func_020155cc(UnkStruct_02278d28 *p);

void func_ov088_02278d28(UnkStruct_02278d28 *p)
{
    if (func_020e8858(p->unk_B8 + 0x738) == 0) {
        func_ov088_02278f0c(p, 0);
        func_020155cc(p);
    }
}
