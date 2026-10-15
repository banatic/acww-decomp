/* func_ov105_0229e4a8 @ 0x0229e4a8, 0x190 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2BA];
    unsigned char unk_2BA;
    char pad_2BB[0x23BC - 0x2BA - 1];
    void *unk_23BC;
} UnkStruct_0229e4a8;

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229e4a8 *s);
extern int func_ov105_0229c758(UnkStruct_0229e4a8 *s, int a, int b);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov105_0229db70(UnkStruct_0229e4a8 *s);
extern void func_ov105_0229d230(UnkStruct_0229e4a8 *s);
extern void func_ov105_0229cf48(UnkStruct_0229e4a8 *s);
extern int func_ov105_0229d468(UnkStruct_0229e4a8 *s, unsigned char b);
extern int func_ov105_0229d76c(UnkStruct_0229e4a8 *s, unsigned char b);
extern int func_ov105_0229d75c(UnkStruct_0229e4a8 *s, unsigned char b);
extern int func_ov105_0229d428(UnkStruct_0229e4a8 *s, unsigned char b);
extern void func_ov105_0229cadc(UnkStruct_0229e4a8 *s, unsigned char b, int z);
extern int func_ov105_0229d750(UnkStruct_0229e4a8 *s, unsigned char b);
extern int func_ov105_0229d73c(UnkStruct_0229e4a8 *s, unsigned char b);
extern void func_ov105_0229cd7c(UnkStruct_0229e4a8 *s);
extern int func_ov105_0229d78c(UnkStruct_0229e4a8 *s);
extern int func_ov105_0229d7d4(void *receiver);
extern void func_ov105_0229d7f4(UnkStruct_0229e4a8 *s, unsigned char b, int v);
extern void func_ov105_0229c330(UnkStruct_0229e4a8 *s, int v);
extern void func_ov105_0229cfc0(UnkStruct_0229e4a8 *s);
extern void func_ov105_0229c668(UnkStruct_0229e4a8 *s);
extern int func_ov105_0229c354(UnkStruct_0229e4a8 *s);

extern struct {
    char pad2[2];
    unsigned short field;
} data_021fbe40;

void func_ov105_0229e4a8(UnkStruct_0229e4a8 *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014(s) != 0) {
        func_ov105_0229db70(s);
        func_ov002_02207d24((char *) s + 0x23BC, 1);
        return;
    }
    if (func_ov105_0229c758(s, func_ov002_02208008(s), 0) != 0) {
        func_ov105_0229d230(s);
        func_ov105_0229cf48(s);
        func_ov002_02207d24((char *) s + 0x23BC, 0);
        return;
    }
    if (func_ov105_0229d468(s, s->unk_2BA) == 0) {
        val = data_021fbe40.field;
        if (val & 1) {
            if (func_ov105_0229d76c(s, s->unk_2BA) != 0 || func_ov105_0229d75c(s, s->unk_2BA) != 0) {
                if (func_ov105_0229d428(s, s->unk_2BA) == 0) {
                    func_ov105_0229cadc(s, s->unk_2BA, 0);
                }
            } else if (func_ov105_0229d750(s, s->unk_2BA) != 0 || func_ov105_0229d73c(s, s->unk_2BA) != 0) {
                func_ov105_0229cd7c(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov105_0229d76c(s, s->unk_2BA) != 0 || func_ov105_0229d75c(s, s->unk_2BA) != 0) {
                if (func_ov105_0229d428(s, s->unk_2BA) == 0) {
                    if (func_ov105_0229d76c(s, s->unk_2BA) != 0) {
                        r = func_ov105_0229d78c(s);
                    } else {
                        r = func_ov105_0229d7d4(s);
                    }
                    if (r != 0x40) {
                        func_ov105_0229d7f4(s, s->unk_2BA, r);
                        func_ov002_02207d24((char *) s + 0x23BC, 1);
                        func_ov105_0229c330(s, 0x1000);
                    }
                }
            }
            return;
        }
    }
    val = data_021fbe40.field;
    if ((val & 8) || (val & 2)) {
        func_ov105_0229cfc0(s);
        func_ov105_0229c668(s);
        func_ov002_02207d24((char *) s + 0x23BC, 0);
        return;
    }
    if (func_ov105_0229c354(s) == 0) {
        func_ov002_02207d00((char *) s + 0x23BC);
    }
}
