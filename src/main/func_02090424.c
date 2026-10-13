/* func_02090424 @ 0x02090424, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int m[12];
} M43;
typedef struct {
    int x, y, z, w;
} Vec4;

extern M43 data_021fbe48;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    short unk_1C;
    short unk_1E;
    short unk_20;
    short unk_22;
    char unk_24[0x80 - 0x24];
    int unk_80;
    int unk_84;
    M43 unk_88;
} UnkStruct_02090424;

extern int func_0203f8d0(Vec4 *out, int *src);
extern void func_020e96c8(M43 *m, int a, int b, int c);
extern void func_020e9774(M43 *m, int a);
extern void func_020e97a4(M43 *m, short a, short b, short c);
extern void func_020e9838(M43 *m, int a, int b, int c);
extern void func_0205510c(void *p, int a);
extern unsigned short func_02065604(void);
extern void NNS_G3dMdlSetMdlEmi(int a, int b, unsigned short c);

void func_02090424(UnkStruct_02090424 *o)
{
    volatile unsigned short a;
    volatile unsigned short b;
    Vec4 v;
    int h;
    if (o->unk_00 != 0) {
        h = func_0203f8d0(&v, &o->unk_04);
        func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
        func_020e9774(&data_021fbe48, h);
        func_020e97a4(&data_021fbe48, o->unk_1C, o->unk_1E, o->unk_20);
        func_020e9838(&data_021fbe48, o->unk_10, o->unk_14, o->unk_18);
        o->unk_88 = data_021fbe48;
        func_0205510c(o->unk_24, 0);
        a = func_02065604();
        b = a;
        NNS_G3dMdlSetMdlEmi(o->unk_80, 0, b);
    }
}
