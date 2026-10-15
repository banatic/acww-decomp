/* func_020929fc @ 0x020929fc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct GX_tag {
    char pad_00[0x1c];
    unsigned short unk_1C;
} GX;

extern GX data_021d5658;
extern void func_02091494(GX *, unsigned short, int, int, int, int, int);
extern int func_02090ac4(int, int, int, void *);
extern void func_020914dc(GX *);
extern char data_020e2a3c[];

int func_020929fc(int a, int b, int c, int d)
{
    GX *p = &data_021d5658;
    GX *q = p;
    int result = 3;

    func_02091494(p, q->unk_1C, a, b, c, d, -181);
    if (func_02090ac4(126, b, c, data_020e2a3c) != 0) {
        result = 0;
    }
    func_020914dc(p);
    return result;
}
