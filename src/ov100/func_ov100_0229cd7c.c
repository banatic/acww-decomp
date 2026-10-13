/* func_ov100_0229cd7c @ 0x0229cd7c, 0x78 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xcc];
    char sub[0x2918 - 0xcc];
    unsigned short unk_2918;
    char pad_291A[2];
    unsigned char unk_291C;
    unsigned char unk_291D;
} UnkStruct_0229cd7c;

extern int func_ov100_0229d630(void);
extern int func_ov100_0229d620(UnkStruct_0229cd7c *p, int n);
extern int func_ov100_0229d5d4(UnkStruct_0229cd7c *p, int n);
extern int func_ov094_0229aaac(void *sub, int v);
extern int func_ov094_0229aa84(void *sub, int v);
extern void func_ov094_0229aa58(void *sub, int v);
extern void func_ov094_0229a99c(void *sub, unsigned short a, unsigned char b);

void func_ov100_0229cd7c(UnkStruct_0229cd7c *p, int n)
{
    int result;

    if (func_ov100_0229d630() == 0 && func_ov100_0229d620(p, n) == 0) {
        return;
    }

    result = func_ov100_0229d5d4(p, n);
    p->unk_291D = 1;
    p->unk_2918 = (unsigned short) func_ov094_0229aaac(&p->sub, result);
    p->unk_291C = (unsigned char) func_ov094_0229aa84(&p->sub, result);
    func_ov094_0229aa58(&p->sub, result);
    func_ov094_0229a99c(&p->sub, p->unk_2918, p->unk_291C);
}
