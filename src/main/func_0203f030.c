/* func_0203f030 @ 0x0203f030, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200354c(void);
extern void func_0203edf4(void *p, unsigned int val);
extern void func_0203eddc(void *p);

struct UnkStruct_0203f030 {
    unsigned char pad_00[0xdc];
    int unk_DC;
    void *unk_E0;
    unsigned char pad_E4[4];
    short unk_E8;
};

int func_0203f030(void *p)
{
    struct UnkStruct_0203f030 *s = (struct UnkStruct_0203f030 *) p;
    if (func_0200354c() == 0) {
        return 0;
    }
    s->unk_DC = 0;
    s->unk_E0 = p;
    func_0203edf4(p, 0x3000);
    s->unk_E8 = 0;
    func_0203eddc(p);
    return 1;
}
