/* func_ov104_0229e3b8 @ 0x0229e3b8, 0x194 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xB8];
    unsigned char unk_B8;
    char pad_B9[0x23B8 - 0xB8 - 1];
    void *unk_23B8;
} UnkStruct_0229e3b8;

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229e3b8 *s);
extern int func_ov104_0229cc30(UnkStruct_0229e3b8 *s, int a, int b);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov104_0229dd54(UnkStruct_0229e3b8 *s);
extern void func_ov104_0229d5c0(UnkStruct_0229e3b8 *s);
extern void func_ov104_0229d304(UnkStruct_0229e3b8 *s);
extern int func_ov104_0229d7fc(UnkStruct_0229e3b8 *s, unsigned char b);
extern int func_ov104_0229da80(UnkStruct_0229e3b8 *s, unsigned char b);
extern int func_ov104_0229da70(UnkStruct_0229e3b8 *s, unsigned char b);
extern int func_ov104_0229d7bc(UnkStruct_0229e3b8 *s, unsigned char b);
extern void func_ov104_0229cf14(UnkStruct_0229e3b8 *s, unsigned char b, int z);
extern int func_ov104_0229da5c(UnkStruct_0229e3b8 *s, unsigned char b);
extern void func_ov104_0229d178(UnkStruct_0229e3b8 *s);
extern int func_ov104_0229daa0(UnkStruct_0229e3b8 *s);
extern int func_ov104_0229dad8(void *receiver);
extern void func_ov104_0229daf8(UnkStruct_0229e3b8 *s, unsigned char b, int v);
extern void func_ov104_0229d378(UnkStruct_0229e3b8 *s);
extern void func_ov104_0229c9fc(UnkStruct_0229e3b8 *s);
extern void func_ov104_0229ca44(UnkStruct_0229e3b8 *s);

extern struct {
    char pad2[2];
    unsigned short field;
} data_021fbe40;

void func_ov104_0229e3b8(UnkStruct_0229e3b8 *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014(s) != 0) {
        func_ov104_0229dd54(s);
        func_ov002_02207d24((char *) s + 0x23B8, 1);
        return;
    }
    if (func_ov104_0229cc30(s, func_ov002_02208008(s), 0) != 0) {
        func_ov104_0229d5c0(s);
        func_ov104_0229d304(s);
        func_ov002_02207d24((char *) s + 0x23B8, 0);
        return;
    }
    if (func_ov104_0229d7fc(s, s->unk_B8) == 0) {
        val = data_021fbe40.field;
        if (val & 1) {
            if (func_ov104_0229da80(s, s->unk_B8) != 0 || func_ov104_0229da70(s, s->unk_B8) != 0) {
                if (func_ov104_0229d7bc(s, s->unk_B8) == 0) {
                    func_ov104_0229cf14(s, s->unk_B8, 0);
                }
            } else if (func_ov104_0229da5c(s, s->unk_B8) != 0) {
                func_ov104_0229d178(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov104_0229da80(s, s->unk_B8) != 0 || func_ov104_0229da70(s, s->unk_B8) != 0) {
                if (func_ov104_0229d7bc(s, s->unk_B8) == 0) {
                    if (func_ov104_0229da80(s, s->unk_B8) != 0) {
                        r = func_ov104_0229daa0(s);
                    } else {
                        r = func_ov104_0229dad8(s);
                    }
                    if (r != 0x21) {
                        func_ov104_0229daf8(s, s->unk_B8, r);
                        func_ov002_02207d24((char *) s + 0x23B8, 1);
                    }
                }
            }
            return;
        }
    }
    val = data_021fbe40.field;
    if (val & 2) {
        func_ov104_0229d378(s);
        func_ov104_0229c9fc(s);
        func_ov002_02207d24((char *) s + 0x23B8, 0);
        return;
    }
    if (val & 8) {
        func_ov104_0229d378(s);
        func_ov104_0229ca44(s);
        func_ov002_02207d24((char *) s + 0x23B8, 0);
        return;
    }
    func_ov002_02207d00((char *) s + 0x23B8);
}
