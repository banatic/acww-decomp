/* func_0209418c @ 0x0209418c, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034270(void *dst, int src, int c, int d);
extern void func_0203423c(void *src);
extern int func_02094cf8(int a, int b, void *c, int d, int e, int f);
extern int func_02094840(int a, int b, void *c, int d, int e, void (*callback)(void *));
extern void func_02091494(void *g, unsigned short val, int p0, void *p1, int p2, int p3, int p4);
extern int func_02090ac4(int a, void *b, int c, int d);
extern void func_020914dc(void *a);

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0209418c;

typedef struct {
    unsigned char pad_00[0x30];
    int unk_30;
    unsigned char pad_34[0x8];
    int unk_3C;
} LocalBuf;

extern unsigned short data_021d52d8[];

extern unsigned char data_021d5658[];

int func_0209418c(int a0, UnkStruct_0209418c *a1, int a2, int a3, int a4, int a5, void (*callback)(void *))
{
    LocalBuf buf;
    unsigned short *p = data_021d52d8;
    int result;

    func_02034270(&buf, (int) a1, 0, 0);
    result = 3;
    if (buf.unk_30 != 0) {
        a1->unk_04 = buf.unk_3C;
    }
    if (func_02094cf8(0x4a, a0, (void *) a1, a2, a3, a5) < 3) {
        func_02094840(2, a0, (void *) a1, a2, a3, callback);
        func_02091494((void *) data_021d5658, p[0x1ce], a0, (void *) a1, a2, a3, -1);
        if (func_02090ac4(0x45, (void *) a1, a2, a4) != 0) {
            result = 2;
        }
    }
    func_020914dc((void *) data_021d5658);
    func_0203423c(&buf);
    return result;
}
