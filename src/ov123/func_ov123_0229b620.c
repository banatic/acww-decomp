/* func_ov123_0229b620 @ 0x0229b620, 0x24 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207fc0(void *);
extern void func_ov123_02299d44(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

typedef struct {
    char pad_00[0xaa];
    unsigned char unk_AA;
} UnkStruct_0229b620;

void func_ov123_0229b620(UnkStruct_0229b620 *self)
{
    func_ov002_02207fc0(self);
    self->unk_AA = 0x20;
    func_ov123_02299d44(self);
    func_ov002_02208098(self, 8);
}
