/* outdoor_villager_acts_2: 3 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02267634 @ 0x02267634, 0x74 bytes, Thumb
 * func_ov068_022675c8 @ 0x022675c8, 0x6c bytes, Thumb
 * func_ov068_022675c4 @ 0x022675c4, 0x2 bytes, Thumb
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

extern int func_02016104(int);
extern void func_02013aac(int);
extern int func_0201c314(int, int);
extern void func_ov068_02266c34(int, int, int, int, int, int, int, int, int);
extern int func_020147fc(int, int, int, int);
extern int data_021fbee8;
extern int data_020c814c;
extern int func_02014868(unsigned char *);
extern void func_ov068_0226ad78(UnkStruct_022675c8 *, UnkStruct_022675c8_2 *, int, int, int);
extern void func_0203eddc(UnkStruct_022675c8_2 *);
extern int func_0203e020(UnkStruct_022675c8_2 *);
extern void func_0201ce5c(UnkStruct_022675c8_2 *, int);
extern void func_ov068_0226cce4(UnkStruct_022675c8 *, int);
extern void func_0201ce44(UnkStruct_022675c8_2 *, int);

int func_ov068_02267634(int param0, int param1)
{
    int r4, r6;
    r4 = func_02016104(param1 + 0x680);
    r6 = 0;
    func_02013aac(param1);
    if (r4 != 0) {
        r6 = func_0201c314(param1, r4);
    }
    func_ov068_02266c34(param1 + 0x898, param1, 1, 0, 0, (int) &data_021fbee8, 4, data_020c814c, 1);
    func_020147fc(param1 + 0x618, 0, r6, 0);
    return 1;
}

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

void func_ov068_022675c4(void *object, int event) {}
