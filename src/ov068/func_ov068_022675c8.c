/* func_ov068_022675c8 @ 0x022675c8, 0x6c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1C];
    unsigned char unk_1C;
    unsigned char pad1[0xD7];
    int unk_F4;
} UnkStruct_022675c8;

typedef struct {
    unsigned char pad_00[0x618];
    unsigned char unk_618[1];
    unsigned char pad1[0x3F3];
    int unk_A0C;
} UnkStruct_022675c8_2;

extern int func_02014868(unsigned char *);
extern void func_ov068_0226ad78(UnkStruct_022675c8 *, UnkStruct_022675c8_2 *, int, int, int);
extern void func_0203eddc(UnkStruct_022675c8_2 *);
extern void func_0203e020(UnkStruct_022675c8_2 *);
extern void func_0201ce5c(UnkStruct_022675c8_2 *, int);
extern void func_ov068_0226cce4(UnkStruct_022675c8 *, int);
extern void func_0201ce44(UnkStruct_022675c8_2 *, int);

void func_ov068_022675c8(UnkStruct_022675c8 *p0, UnkStruct_022675c8_2 *p1)
{
    if (func_02014868(p1->unk_618) != 0) {
        return;
    }
    func_ov068_0226ad78(p0, p1, 4, 1, 1);
    func_0203eddc(p1);
    func_0203e020(p1);
    func_0201ce5c(p1, 0);
    func_ov068_0226cce4(p0, 0);
    func_0201ce44(p1, 0);
    p1->unk_A0C = 3;
    p0->unk_F4 = 0x4B0;
    p0->unk_1C = 1;
}
