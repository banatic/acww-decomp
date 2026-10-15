/* func_ov110_0229ddb4 @ 0x0229ddb4, 0x178 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xF5];
    unsigned char unk_F5;
    char pad_F6[0x21F8 - 0xF5 - 1];
    void *unk_21F8;
} UnkStruct_0229ddb4;

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229ddb4 *s);
extern int func_ov110_0229c5a0(UnkStruct_0229ddb4 *s, int a, int b);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov110_0229d894(UnkStruct_0229ddb4 *s);
extern void func_ov110_0229ce44(UnkStruct_0229ddb4 *s);
extern void func_ov110_0229cb78(UnkStruct_0229ddb4 *s);
extern int func_ov110_0229d13c(UnkStruct_0229ddb4 *s, unsigned char b);
extern int func_ov110_0229d5e4(UnkStruct_0229ddb4 *s, unsigned char b);
extern int func_ov110_0229d5d4(UnkStruct_0229ddb4 *s, unsigned char b);
extern int func_ov110_0229d0fc(UnkStruct_0229ddb4 *s, unsigned char b);
extern void func_ov110_0229c9c8(UnkStruct_0229ddb4 *s);
extern int func_ov110_0229d5c8(UnkStruct_0229ddb4 *s, unsigned char b);
extern void func_ov110_0229ca08(UnkStruct_0229ddb4 *s);
extern int func_ov110_0229d600(UnkStruct_0229ddb4 *s);
extern unsigned char func_ov110_0229d628(void *receiver);
extern void func_ov110_0229d648(UnkStruct_0229ddb4 *s, unsigned char b, int v);
extern void func_ov110_0229cbe0(UnkStruct_0229ddb4 *s);
extern void func_ov110_0229c3b8(UnkStruct_0229ddb4 *s, int v);

extern struct {
    char pad2[2];
    unsigned short field;
} data_021fbe40;

void func_ov110_0229ddb4(UnkStruct_0229ddb4 *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014(s) != 0) {
        func_ov110_0229d894(s);
        func_ov002_02207d24((char *) s + 0x21F8, 1);
        return;
    }
    if (func_ov110_0229c5a0(s, func_ov002_02208008(s), 0) != 0) {
        func_ov110_0229ce44(s);
        func_ov110_0229cb78(s);
        func_ov002_02207d24((char *) s + 0x21F8, 0);
        return;
    }
    if (func_ov110_0229d13c(s, s->unk_F5) == 0) {
        val = data_021fbe40.field;
        if (val & 1) {
            if (func_ov110_0229d5e4(s, s->unk_F5) != 0 || func_ov110_0229d5d4(s, s->unk_F5) != 0) {
                if (func_ov110_0229d0fc(s, s->unk_F5) == 0) {
                    func_ov110_0229c9c8(s);
                }
            } else if (func_ov110_0229d5c8(s, s->unk_F5) != 0) {
                func_ov110_0229ca08(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov110_0229d5e4(s, s->unk_F5) != 0 || func_ov110_0229d5d4(s, s->unk_F5) != 0) {
                if (func_ov110_0229d0fc(s, s->unk_F5) == 0) {
                    if (func_ov110_0229d5e4(s, s->unk_F5) != 0) {
                        r = func_ov110_0229d600(s);
                    } else {
                        r = func_ov110_0229d628((void *) s);
                    }
                    if (r != 0x1f) {
                        func_ov110_0229d648(s, s->unk_F5, r);
                        func_ov002_02207d24((char *) s + 0x21F8, 1);
                    }
                }
            }
            return;
        }
    }
    val = data_021fbe40.field;
    if ((val & 8) || (val & 2)) {
        func_ov110_0229cbe0(s);
        func_ov002_02207d24((char *) s + 0x21F8, 0);
        func_ov110_0229c3b8(s, 1);
        return;
    }
    func_ov002_02207d00((char *) s + 0x21F8);
}
