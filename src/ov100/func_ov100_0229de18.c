/* func_ov100_0229de18 @ 0x0229de18, 0x180 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x218C];
    void *unk_218C;
    char pad_2190[0x2921 - 0x218C - 4];
    unsigned char unk_2921;
} UnkStruct_0229de18;

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229de18 *s);
extern int func_ov100_0229c60c(UnkStruct_0229de18 *s, int a, int b);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov100_0229d90c(UnkStruct_0229de18 *s);
extern void func_ov100_0229cecc(UnkStruct_0229de18 *s);
extern void func_ov100_0229cbd4(UnkStruct_0229de18 *s);
extern int func_ov100_0229d194(UnkStruct_0229de18 *s, unsigned char b);
extern int func_ov100_0229d630(UnkStruct_0229de18 *s, unsigned char b);
extern int func_ov100_0229d620(UnkStruct_0229de18 *s, unsigned char b);
extern int func_ov100_0229d158(UnkStruct_0229de18 *s, unsigned char b);
extern void func_ov100_0229ca1c(UnkStruct_0229de18 *s);
extern int func_ov100_0229d60c(UnkStruct_0229de18 *s, unsigned char b);
extern void func_ov100_0229ca5c(UnkStruct_0229de18 *s);
extern int func_ov100_0229d648(UnkStruct_0229de18 *s);
extern int func_ov100_0229d67c(void *receiver);
extern void func_ov100_0229d69c(UnkStruct_0229de18 *s, unsigned char b, int v);
extern void func_ov100_0229cc3c(UnkStruct_0229de18 *s);
extern void func_ov100_0229c4ec(UnkStruct_0229de18 *s);
extern void func_ov100_0229c3c0(UnkStruct_0229de18 *s);

extern struct {
    char pad2[2];
    unsigned short field;
} data_021fbe40;

void func_ov100_0229de18(UnkStruct_0229de18 *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014(s) != 0) {
        func_ov100_0229d90c(s);
        func_ov002_02207d24((char *) s + 0x218C, 1);
        return;
    }
    if (func_ov100_0229c60c(s, func_ov002_02208008(s), 0) != 0) {
        func_ov100_0229cecc(s);
        func_ov100_0229cbd4(s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    if (func_ov100_0229d194(s, s->unk_2921) == 0) {
        val = data_021fbe40.field;
        if (val & 1) {
            if (func_ov100_0229d630(s, s->unk_2921) != 0 || func_ov100_0229d620(s, s->unk_2921) != 0) {
                if (func_ov100_0229d158(s, s->unk_2921) == 0) {
                    func_ov100_0229ca1c(s);
                }
            } else if (func_ov100_0229d60c(s, s->unk_2921) != 0) {
                func_ov100_0229ca5c(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov100_0229d630(s, s->unk_2921) != 0 || func_ov100_0229d620(s, s->unk_2921) != 0) {
                if (func_ov100_0229d158(s, s->unk_2921) == 0) {
                    if (func_ov100_0229d630(s, s->unk_2921) != 0) {
                        r = func_ov100_0229d648(s);
                    } else {
                        r = func_ov100_0229d67c((void *) s);
                    }
                    if (r != 0x20) {
                        func_ov100_0229d69c(s, s->unk_2921, r);
                        func_ov002_02207d24((char *) s + 0x218C, 1);
                    }
                }
            }
            return;
        }
    }
    val = data_021fbe40.field;
    if (val & 2) {
        func_ov100_0229cc3c(s);
        func_ov100_0229c4ec(s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    if (val & 8) {
        func_ov100_0229cc3c(s);
        func_ov100_0229c3c0(s);
        func_ov002_02207d24((char *) s + 0x218C, 0);
        return;
    }
    func_ov002_02207d00((char *) s + 0x218C);
}
