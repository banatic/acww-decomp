/* func_ov004_02228038 @ 0x02228038, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct BigStruct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0x7fc - (0x7f0 + 4)];
    int unk_7FC;
} BigStruct;

extern int func_02056f94(char *p);
extern int func_02008258(BigStruct *p, int x);
extern int func_0200c3b0(BigStruct *p, int a, int b, int c);

void func_ov004_02228038(BigStruct *p)
{
    if (func_02056f94((char *) p + 0x2d0)) {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        func_0200c3b0(p, 3, 5, -1);
    }
}
