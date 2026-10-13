/* func_ov105_0229d294 @ 0x0229d294, 0x7c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2b6];
    unsigned char b;
    char pad_2B7[0xd5c - 0x2b7];
    char arr0d5c[1];
    char pad_D5D[0x23bc - 0xd5c - 1];
    char arr23bc[1];
} UnkStruct_0229d294;

extern int func_ov105_0229d530(UnkStruct_0229d294 *, unsigned char);
extern int func_ov105_0229d4c4(UnkStruct_0229d294 *, unsigned char);
extern int func_ov105_0229d76c(UnkStruct_0229d294 *, unsigned char);
extern int func_ov105_0229d75c(UnkStruct_0229d294 *, unsigned char);
extern int func_ov105_0229d718(UnkStruct_0229d294 *, unsigned char);
extern int func_0206fe54(void);
extern void func_0208aa60(char *, int, int);
extern void func_ov094_0229b9b4(char *, char *, int);

void func_ov105_0229d294(UnkStruct_0229d294 *p)
{
    int r6, r4;
    int r2;

    r6 = func_ov105_0229d530(p, p->b) - 0x6d;
    r4 = func_ov105_0229d4c4(p, p->b) - 0x78;
    if (func_0206fe54() != 0) {
        r4 -= 8;
    }
    func_0208aa60(p->arr23bc, r6, r4);
    if (func_ov105_0229d76c(p, p->b) != 0 || func_ov105_0229d75c(p, p->b) != 0) {
        r2 = func_ov105_0229d718(p, p->b);
        func_ov094_0229b9b4(p->arr0d5c, p->arr23bc, r2);
    }
}
