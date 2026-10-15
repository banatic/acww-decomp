/* func_ov106_0229e2dc @ 0x0229e2dc, 0x154 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xB8];
    unsigned char unk_B8;
    char pad_B9[0x21B8 - 0xB8 - 1];
    void *unk_21B8;
} UnkStruct_0229e2dc;

extern int func_ov002_02208014(void);
extern int func_ov002_02208008(UnkStruct_0229e2dc *s);
extern int func_ov106_0229c4a0(UnkStruct_0229e2dc *s, int a, int b);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov106_0229d790(UnkStruct_0229e2dc *s);
extern void func_ov106_0229cea8(UnkStruct_0229e2dc *s);
extern void func_ov106_0229cbdc(UnkStruct_0229e2dc *s);
extern int func_ov106_0229d0d0(UnkStruct_0229e2dc *s, unsigned char b);
extern int func_ov106_0229d3a0(UnkStruct_0229e2dc *s, unsigned char b);
extern int func_ov106_0229d390(UnkStruct_0229e2dc *s, unsigned char b);
extern int func_ov106_0229d090(UnkStruct_0229e2dc *s, unsigned char b);
extern void func_ov106_0229c798(UnkStruct_0229e2dc *s, unsigned char b, int z);
extern int func_ov106_0229d384(UnkStruct_0229e2dc *s, unsigned char b);
extern void func_ov106_0229ca1c(UnkStruct_0229e2dc *s);
extern int func_ov106_0229d48c(UnkStruct_0229e2dc *s);
extern void func_ov106_0229d4ac(UnkStruct_0229e2dc *s, unsigned char b, int v);
extern void func_ov106_0229cc50(UnkStruct_0229e2dc *s);
extern void func_ov106_0229c378(UnkStruct_0229e2dc *s);

extern struct {
    char pad2[2];
    unsigned short field;
} data_021fbe40;

void func_ov106_0229e2dc(UnkStruct_0229e2dc *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014() != 0) {
        func_ov106_0229d790(s);
        func_ov002_02207d24((char *) s + 0x21B8, 1);
        return;
    }
    if (func_ov106_0229c4a0(s, func_ov002_02208008(s), 0) != 0) {
        func_ov106_0229cea8(s);
        func_ov106_0229cbdc(s);
        func_ov002_02207d24((char *) s + 0x21B8, 0);
        return;
    }
    if (func_ov106_0229d0d0(s, s->unk_B8) == 0) {
        val = data_021fbe40.field;
        if (val & 1) {
            if (func_ov106_0229d3a0(s, s->unk_B8) != 0 || func_ov106_0229d390(s, s->unk_B8) != 0) {
                if (func_ov106_0229d090(s, s->unk_B8) == 0) {
                    func_ov106_0229c798(s, s->unk_B8, 0);
                }
            } else if (func_ov106_0229d384(s, s->unk_B8) != 0) {
                func_ov106_0229ca1c(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov106_0229d390(s, s->unk_B8) != 0) {
                if (func_ov106_0229d090(s, s->unk_B8) == 0) {
                    r = func_ov106_0229d48c(s);
                    if (r != 0x20) {
                        func_ov106_0229d4ac(s, s->unk_B8, r);
                        func_ov002_02207d24((char *) s + 0x21B8, 1);
                    }
                }
            }
            return;
        }
    }
    val = data_021fbe40.field;
    if ((val & 8) || (val & 2)) {
        func_ov106_0229cc50(s);
        func_ov106_0229c378(s);
        func_ov002_02207d24((char *) s + 0x21B8, 0);
        return;
    }
    func_ov002_02207d00((char *) s + 0x21B8);
}
