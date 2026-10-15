/* func_ov107_0229d3f8 @ 0x0229d3f8, 0x88 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

typedef struct Something {
    unsigned char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    unsigned char pad_A4[0xb6 - (0xa0 + 4)];
    unsigned char unk_B6;
    unsigned char unk_B7;
    unsigned char pad_B8[0xbf - (0xb7 + 1)];
    unsigned char unk_BF;
    unsigned char pad_C0[0x21cc - (0xbf + 1)];
    char unk_21CC;
} Something;

extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_02207cf8(char *p);
extern void func_ov002_02207d00(char *p);
extern int func_ov107_0229d29c(Something *p, unsigned char b);
extern int func_ov107_0229d260(Something *p, unsigned char b);
extern int func_ov107_0229d15c(Something *p, int val);
extern void func_ov094_022999cc(void);

void func_ov107_0229d3f8(Something *p, int val)
{
    unsigned char a;
    unsigned char b;
    int r;

    p->unk_B6 = val;
    func_ov002_02208098((void *) (p), 1);
    a = data_021f6c58;
    b = data_021f6c54;
    r = func_ov107_0229d29c(p, p->unk_B6);
    p->unk_9C = r - a;
    r = func_ov107_0229d260(p, p->unk_B6);
    p->unk_A0 = r - b;
    p->unk_B7 = val;
    func_ov002_02207cf8(&p->unk_21CC);
    func_ov002_02207d00(&p->unk_21CC);
    p->unk_BF = 2;
    if (func_ov107_0229d15c(p, val) == 0) {
        func_ov094_022999cc();
    }
}
