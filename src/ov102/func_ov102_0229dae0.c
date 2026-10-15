/* func_ov102_0229dae0 @ 0x0229dae0, 0x164 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x25A2];
    unsigned char unk_25A2;
    unsigned char unk_25A3;
    char pad_25A4[1];
    unsigned char unk_25A5;
    char pad_25A6[4];
    unsigned char unk_25AA;
} UnkStruct_0229dae0;

extern int func_0206f56c(void);
extern int func_ov002_02208008(UnkStruct_0229dae0 *s);
extern int func_ov102_0229c560(UnkStruct_0229dae0 *s, int a, int b);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov102_0229cc60(UnkStruct_0229dae0 *s, unsigned char b);
extern void func_ov102_0229cb50(UnkStruct_0229dae0 *s);
extern void func_ov102_0229c460(UnkStruct_0229dae0 *s, int v);
extern void func_ov102_0229cdf4(UnkStruct_0229dae0 *s);
extern void func_ov102_0229cab8(UnkStruct_0229dae0 *s);
extern int func_ov102_0229d464(UnkStruct_0229dae0 *s, unsigned char b);
extern int func_ov102_0229d454(UnkStruct_0229dae0 *s, unsigned char b);
extern int func_ov102_0229d0b0(UnkStruct_0229dae0 *s, unsigned char b);
extern int func_ov102_0229d074(UnkStruct_0229dae0 *s, unsigned char b);
extern void func_ov102_0229c9fc(UnkStruct_0229dae0 *s, unsigned char b);
extern void func_ov102_0229c9b0(UnkStruct_0229dae0 *s, unsigned char b);
extern int func_ov102_0229d444(UnkStruct_0229dae0 *s, unsigned char b);
extern void func_ov102_0229ca78(UnkStruct_0229dae0 *s);
extern void func_ov102_0229d54c(UnkStruct_0229dae0 *s, unsigned char b, int v);
extern int func_0208e4bc(void *p);
extern int func_ov102_0229c2c0(UnkStruct_0229dae0 *s);
extern void func_ov102_0229cd38(UnkStruct_0229dae0 *s);

extern struct {
    char pad2[2];
    unsigned short field;
} data_021fbe40;

void func_ov102_0229dae0(UnkStruct_0229dae0 *s)
{
    unsigned short val;
    if (func_0206f56c() != 0) {
        func_ov102_0229cc60(s, s->unk_25A2);
        func_ov102_0229cb50(s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        func_ov102_0229c460(s, 0);
        return;
    }
    if (func_ov102_0229c560(s, func_ov002_02208008(s), 1) != 0) {
        func_ov102_0229cdf4(s);
        func_ov102_0229cab8(s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    val = data_021fbe40.field;
    if (val & 1) {
        if (func_ov102_0229d464(s, s->unk_25A5) != 0 || func_ov102_0229d454(s, s->unk_25A5) != 0) {
            if (func_ov102_0229d0b0(s, s->unk_25A5) == 0) {
                if (func_ov102_0229d074(s, s->unk_25A5) != 0) {
                    func_ov102_0229c9fc(s, s->unk_25A5);
                } else {
                    func_ov102_0229c9b0(s, s->unk_25A5);
                }
            }
        } else if (func_ov102_0229d444(s, s->unk_25A5) != 0) {
            func_ov102_0229ca78(s);
        }
        return;
    }
    if (val & 2) {
        if (func_ov102_0229d454(s, s->unk_25A2) != 0) {
            if (s->unk_25A3 != s->unk_25AA) {
                func_ov102_0229d54c(s, (unsigned char) (s->unk_25A3 + 0x1e), 4);
                return;
            }
        }
        if (func_0208e4bc((char *) s + 0x2274) == 1) {
            func_ov102_0229d54c(s, s->unk_25A2, 4);
        } else {
            func_ov102_0229c9fc(s, s->unk_25A2);
        }
        return;
    }
    if (func_ov102_0229c2c0(s) == 0) {
        func_ov102_0229cd38(s);
        func_ov002_02207d00((char *) s + 0x218C);
    }
}
