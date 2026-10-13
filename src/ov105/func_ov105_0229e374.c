/* func_ov105_0229e374 @ 0x0229e374, 0x134 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2B7];
    unsigned char unk_2B7;
    unsigned char unk_2B8;
    char pad_2B9[1];
    unsigned char unk_2BA;
    char pad_2BB[5];
    unsigned char unk_2C0;
    char pad_2C1[0x23BC - 0x2C0 - 1];
    void *unk_23BC;
    char pad2[0x24A4 - 0x23BC - 4];
    char unk_24A4;
} UnkStruct_0229e374;

extern int func_ov002_02208008(UnkStruct_0229e374 *s);
extern int func_ov105_0229c758(UnkStruct_0229e374 *s, int a, int b);
extern void func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov105_0229d230(UnkStruct_0229e374 *s);
extern void func_ov105_0229cf48(UnkStruct_0229e374 *s);
extern int func_ov105_0229d76c(UnkStruct_0229e374 *s, unsigned char b);
extern int func_ov105_0229d75c(UnkStruct_0229e374 *s, unsigned char b);
extern int func_ov105_0229d468(UnkStruct_0229e374 *s, unsigned char b);
extern int func_ov105_0229d428(UnkStruct_0229e374 *s, unsigned char b);
extern void func_ov105_0229ccf4(UnkStruct_0229e374 *s, unsigned char b);
extern void func_ov105_0229cca8(UnkStruct_0229e374 *s, unsigned char b);
extern int func_ov105_0229d73c(UnkStruct_0229e374 *s, unsigned char b);
extern void func_ov105_0229cd7c(UnkStruct_0229e374 *s);
extern void func_ov105_0229d870(UnkStruct_0229e374 *s, unsigned char b, int v);
extern int func_0208e4bc(void *p);
extern int func_ov105_0229c354(UnkStruct_0229e374 *s);
extern void func_ov105_0229d17c(UnkStruct_0229e374 *s);

extern struct {
    char pad2[2];
    unsigned short field;
} data_021fbe40;

void func_ov105_0229e374(UnkStruct_0229e374 *s)
{
    unsigned short val;
    if (func_ov105_0229c758(s, func_ov002_02208008(s), 1) != 0) {
        func_ov105_0229d230(s);
        func_ov105_0229cf48(s);
        func_ov002_02207d24((char *) s + 0x23BC, 0);
        return;
    }
    val = data_021fbe40.field;
    if (val & 1) {
        if (func_ov105_0229d76c(s, s->unk_2BA) != 0 || func_ov105_0229d75c(s, s->unk_2BA) != 0) {
            if (func_ov105_0229d468(s, s->unk_2BA) == 0) {
                if (func_ov105_0229d428(s, s->unk_2BA) != 0) {
                    func_ov105_0229ccf4(s, s->unk_2BA);
                } else {
                    func_ov105_0229cca8(s, s->unk_2BA);
                }
            }
        } else if (func_ov105_0229d73c(s, s->unk_2BA) != 0) {
            func_ov105_0229cd7c(s);
        }
        return;
    }
    if (val & 2) {
        if (func_ov105_0229d75c(s, s->unk_2B7) != 0) {
            if (s->unk_2B8 != s->unk_2C0) {
                func_ov105_0229d870(s, (unsigned char) (s->unk_2B8 + 0x3e), 4);
                return;
            }
        }
        if (func_0208e4bc((char *) s + 0x24A4) == 1) {
            func_ov105_0229d870(s, s->unk_2B7, 4);
        } else {
            func_ov105_0229ccf4(s, s->unk_2B7);
        }
        return;
    }
    if (func_ov105_0229c354(s) == 0) {
        func_ov105_0229d17c(s);
        func_ov002_02207d00((char *) s + 0x23BC);
    }
}
