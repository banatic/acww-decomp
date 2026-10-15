/* func_ov104_0229dc68 @ 0x0229dc68, 0x98 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0xb5 - 0xa8];
    unsigned char unk_B5;
    unsigned char unk_B6;
    char pad_B7[0xbf - 0xb7];
    unsigned char unk_BF;
    char pad_C0[0x23b8 - 0xc0];
    char subobj;
} UnkStruct_0229dc68;

extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov104_0229d8a8(UnkStruct_0229dc68 *p, unsigned char b);
extern int func_ov104_0229d858(UnkStruct_0229dc68 *p, unsigned char b);
extern void func_ov002_02207cf8(void *p);
extern void func_ov002_02207d00(void *p);
extern int func_ov104_0229d7fc(UnkStruct_0229dc68 *p, int arg);
extern void func_ov104_0229c344(UnkStruct_0229dc68 *p, int arg);
extern void func_ov104_0229c354(UnkStruct_0229dc68 *p, int arg);
extern void func_ov094_022999cc(void);

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov104_0229dc68(UnkStruct_0229dc68 *p, int param1)
{
    unsigned char g1;
    unsigned char g2;

    p->unk_B5 = param1;
    func_ov002_02208098((void *) (p), 1);
    g1 = data_021f6c58;
    g2 = data_021f6c54;
    p->unk_A0 = func_ov104_0229d8a8(p, p->unk_B5) - g1;
    p->unk_A4 = func_ov104_0229d858(p, p->unk_B5) - g2;
    p->unk_B6 = param1;
    func_ov002_02207cf8(&p->subobj);
    func_ov002_02207d00(&p->subobj);
    p->unk_BF = 2;
    if (func_ov104_0229d7fc(p, param1) != 0) {
        func_ov104_0229c344(p, 4);
    } else {
        func_ov104_0229c354(p, 4);
        func_ov094_022999cc();
    }
}
