/* func_ov110_0229cd14 @ 0x0229cd14, 0x78 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229cd14 UnkStruct_0229cd14;
struct UnkStruct_0229cd14 {
    unsigned char pad_00[0xEC];
    unsigned short unk_EC;
    unsigned char pad_EE[2];
    unsigned char unk_F0;
    unsigned char unk_F1;
};

extern int func_ov110_0229d5e4(void *a, void *b);
extern int func_ov110_0229d5d4(void *a, void *b);
extern int func_ov110_0229d590(void *a, void *b);
extern int func_ov094_0229aaac(void *p, int v);
extern int func_ov094_0229aa84(void *p, int v);
extern void func_ov094_0229aa58(void *p, int v);
extern void func_ov094_0229a99c(void *p, int v1, int v2);

void func_ov110_0229cd14(UnkStruct_0229cd14 *a, void *b)
{
    if (func_ov110_0229d5e4(a, b) || func_ov110_0229d5d4(a, b)) {
        int ret = func_ov110_0229d590(a, b);
        a->unk_F1 = 1;
        a->unk_EC = func_ov094_0229aaac((char *) a + 0x138, ret);
        a->unk_F0 = func_ov094_0229aa84((char *) a + 0x138, ret);
        func_ov094_0229aa58((char *) a + 0x138, ret);
        func_ov094_0229a99c((char *) a + 0x138, a->unk_EC, a->unk_F0);
    }
}
