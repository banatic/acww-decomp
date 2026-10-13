/* func_ov096_022a0af0 @ 0x022a0af0, 0x138 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xB5];
    unsigned char unk_B5;
    char pad_B6[0x2418 - 0xB5 - 1];
    void *unk_2418;
} UnkStruct_022a0af0;

extern int func_ov002_02208014(UnkStruct_022a0af0 *s);
extern int func_ov002_02208008(UnkStruct_022a0af0 *s);
extern int func_ov096_0229c560(UnkStruct_022a0af0 *s, int a, int b);
extern void func_ov096_0229eb14(UnkStruct_022a0af0 *s);
extern void func_ov096_0229dd94(UnkStruct_022a0af0 *s);
extern void func_ov002_02207d24(void *p, int v);
extern void func_ov002_02207d00(void *p);
extern void func_ov096_0229fbf0(UnkStruct_022a0af0 *s);
extern int func_ov096_0229f830(UnkStruct_022a0af0 *s, unsigned char b);
extern int func_ov096_0229f820(UnkStruct_022a0af0 *s, unsigned char b);
extern int func_ov096_0229f150(UnkStruct_022a0af0 *s, unsigned char b);
extern void func_ov096_0229cc74(UnkStruct_022a0af0 *s, unsigned char b, int zero);
extern int func_ov096_0229f810(UnkStruct_022a0af0 *s, unsigned char b);
extern void func_ov096_0229dc08(UnkStruct_022a0af0 *s);
extern int func_ov090_02299078(int zero);
extern int func_ov090_02299098(int zero);
extern void func_ov096_022a18dc(UnkStruct_022a0af0 *s, int v);

extern struct {
    char pad2[2];
    unsigned short field;
} data_021fbe40;

void func_ov096_022a0af0(UnkStruct_022a0af0 *s)
{
    if (func_ov002_02208014(s) != 0) {
        func_ov096_0229fbf0(s);
        func_ov002_02207d24((char *) s + 0x2418, 1);
    } else {
        if (func_ov096_0229c560(s, func_ov002_02208008(s), 0) != 0) {
            func_ov096_0229eb14(s);
            func_ov096_0229dd94(s);
            func_ov002_02207d24((char *) s + 0x2418, 0);
        } else {
            unsigned short val = data_021fbe40.field;
            if (val & 1) {
                if (func_ov096_0229f830(s, s->unk_B5) != 0 || func_ov096_0229f820(s, s->unk_B5) != 0) {
                    if (func_ov096_0229f150(s, s->unk_B5) == 0) {
                        func_ov096_0229cc74(s, s->unk_B5, 0);
                    }
                } else {
                    if (func_ov096_0229f810(s, s->unk_B5) != 0) {
                        func_ov096_0229dc08(s);
                    } else {
                        if (s->unk_B5 == 0x25) {
                            func_ov096_0229cc74(s, 0x25, 0);
                        } else if (s->unk_B5 == 0x24) {
                            func_ov096_0229cc74(s, 0x24, 0);
                        }
                    }
                }
            } else if (val & 0x100) {
                func_ov096_022a18dc(s, func_ov090_02299078(0));
            } else if (val & 0x200) {
                func_ov096_022a18dc(s, func_ov090_02299098(0));
            } else if (val & 2) {
                func_ov096_022a18dc(s, 7);
            } else {
                func_ov002_02207d00((char *) s + 0x2418);
            }
        }
    }
}
