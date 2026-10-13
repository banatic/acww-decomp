/* func_ov110_0229d7b8 @ 0x0229d7b8, 0x88 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern void func_ov002_02208098(void *p, int arg);
extern void func_ov002_02207cf8(void *p);
extern void func_ov094_022999cc(void);

extern int func_ov110_0229d3d8(void *p, int b);
extern int func_ov110_0229d388(void *p, int b);
extern int func_ov110_0229d13c(void *p, int arg);
extern void func_ov110_0229c2a8(void *p, int arg);
extern void func_ov110_0229c2b8(void *p, int arg);

typedef struct Context {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0xf2 - 0xa8];
    unsigned char unk_F2;
    unsigned char unk_F3;
} Context;

void func_ov110_0229d7b8(Context *p, int arg1)
{
    unsigned char g1, g2;

    p->unk_F2 = (unsigned char) arg1;
    func_ov002_02208098(p, 1);
    g1 = data_021f6c58;
    g2 = data_021f6c54;
    p->unk_A0 = func_ov110_0229d3d8(p, p->unk_F2) - g1;
    p->unk_A4 = func_ov110_0229d388(p, p->unk_F2) - g2;
    p->unk_F3 = (unsigned char) arg1;
    func_ov002_02207cf8((char *) p + 0x21f8);
    if (func_ov110_0229d13c(p, arg1) != 0) {
        func_ov110_0229c2a8(p, 4);
    } else {
        func_ov110_0229c2b8(p, 4);
        func_ov094_022999cc();
    }
}
