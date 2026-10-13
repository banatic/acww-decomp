/* func_02018cf0 @ 0x02018cf0, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201b1a4(char *dst, char *base, int a, int b, int c);
extern void func_0201b044(char *dst, const char *src);
extern void func_0201afd4(char *dst, const char *src);
extern void func_0201b350(char *dst, int v);
extern void func_02016764(char *a, char *b, int c, int d, int e, int f, int g, int h);
extern void func_02019af0(char *a, int b);
extern void func_0200456c(int a);
extern char data_021fbee8;

typedef struct {
    char pad_00[0x1c];
    unsigned short unk_1C;
} FieldStruct;

extern FieldStruct *func_02019de4(char *arg);

void func_02018cf0(char *arg0, char *arg1)
{
    FieldStruct *t;
    t = func_02019de4(arg0);
    func_0201b1a4(arg1 + 0x350, arg1, 0, 0, t->unk_1C);
    func_0201b044(arg1 + 0x350, &data_021fbee8);
    func_0201afd4(arg1 + 0x350, &data_021fbee8);
    func_0201b350(arg1 + 0x3aa, -2);
    func_02016764(arg1 + 0x334, arg1, 0x77, t->unk_1C, 1, 0x1000, 0, 0);
    func_02019af0(arg0, 0);
    func_0200456c(0xa0);
    arg0[0x98] = 0;
}
