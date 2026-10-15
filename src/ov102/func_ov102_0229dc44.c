/* func_ov102_0229dc44 @ 0x0229dc44, 0x188 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x218C];
    void *unk_218C;
    char pad_2190[0x25A5 - 0x218C - 4];
    unsigned char unk_25A5;
} UnkStruct_0229dc44;

extern int func_ov002_02208014(void);
extern int func_ov002_02208008(UnkStruct_0229dc44 *s);
extern int func_ov102_0229c560(UnkStruct_0229dc44 *s, int a, int b);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov102_0229d79c(UnkStruct_0229dc44 *s);
extern void func_ov102_0229cdf4(UnkStruct_0229dc44 *s);
extern void func_ov102_0229cab8(UnkStruct_0229dc44 *s);
extern int func_ov102_0229d0b0(UnkStruct_0229dc44 *s, unsigned char b);
extern int func_ov102_0229d464(UnkStruct_0229dc44 *s, unsigned char b);
extern int func_ov102_0229d454(UnkStruct_0229dc44 *s, unsigned char b);
extern int func_ov102_0229d074(UnkStruct_0229dc44 *s, unsigned char b);
extern void func_ov102_0229ca38(UnkStruct_0229dc44 *s);
extern int func_ov102_0229d438(UnkStruct_0229dc44 *s, unsigned char b);
extern void func_ov102_0229ca78(UnkStruct_0229dc44 *s);
extern int func_ov102_0229d444(UnkStruct_0229dc44 *s, unsigned char b);
extern int func_ov102_0229d47c(UnkStruct_0229dc44 *s);
extern int func_ov102_0229d4ac(void);
extern void func_ov102_0229d4cc(UnkStruct_0229dc44 *s, unsigned char b, int v);
extern void func_ov102_0229cb50(UnkStruct_0229dc44 *s);
extern void func_ov102_0229c460(UnkStruct_0229dc44 *s, int v);
extern int func_ov102_0229c2c0(UnkStruct_0229dc44 *s);

extern struct {
    char pad2[2];
    unsigned short field;
} data_021fbe40;

void func_ov102_0229dc44(UnkStruct_0229dc44 *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014() != 0) {
        func_ov102_0229d79c(s);
        func_ov002_02207d24((char *) s + 0x218C, 1);
        return;
    }
    if (func_ov102_0229c560(s, func_ov002_02208008(s), 0) != 0) {
        func_ov102_0229cdf4(s);
        func_ov102_0229cab8(s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    if (func_ov102_0229d0b0(s, s->unk_25A5) == 0) {
        val = data_021fbe40.field;
        if (val & 1) {
            if (func_ov102_0229d464(s, s->unk_25A5) != 0 || func_ov102_0229d454(s, s->unk_25A5) != 0) {
                if (func_ov102_0229d074(s, s->unk_25A5) == 0) {
                    func_ov102_0229ca38(s);
                }
            } else if (func_ov102_0229d438(s, s->unk_25A5) != 0) {
                func_ov102_0229ca78(s);
            } else if (func_ov102_0229d444(s, s->unk_25A5) != 0) {
                func_ov102_0229ca78(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov102_0229d464(s, s->unk_25A5) != 0 || func_ov102_0229d454(s, s->unk_25A5) != 0) {
                if (func_ov102_0229d074(s, s->unk_25A5) == 0) {
                    if (func_ov102_0229d464(s, s->unk_25A5) != 0) {
                        r = func_ov102_0229d47c(s);
                    } else {
                        asm {
                            mov r0, s
                        }
                        r = func_ov102_0229d4ac();
                    }
                    if (r != 0x25) {
                        func_ov102_0229d4cc(s, s->unk_25A5, r);
                        func_ov002_02207d24((char *) s + 0x218C, 1);
                    }
                }
            }
            return;
        }
    }
    val = data_021fbe40.field;
    if ((val & 8) || (val & 2)) {
        func_ov102_0229cb50(s);
        func_ov102_0229c460(s, 1);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    if (func_ov102_0229c2c0(s) == 0) {
        func_ov002_02207d00((char *) s + 0x218C);
    }
}
