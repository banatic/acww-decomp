/* func_0203d930 @ 0x0203d930, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x34 - 0x1f];
} LocalT;

extern int data_021c69b4;

extern void func_0203d540(LocalT *self);
extern void func_0203d4d4(LocalT *self, int flag);
extern void func_020a8164(LocalT *self, int val);
extern void func_0203d4cc(LocalT *self, void *a);
extern void func_0203d4c8(LocalT *self, void *d);
extern void func_0203d4d0(LocalT *self, int f);
extern void func_0203d668(int *g);
extern int func_0203d564(int *g, LocalT *self);
extern void func_0203d528(LocalT *self);

int func_0203d930(void *p0, void *p1, void *p2, void *p3, const unsigned char *p4, int p5)
{
    LocalT local;
    int v1, v2, v3;
    int result;

    func_0203d540(&local);
    func_0203d4d4(&local, 0);
    func_020a8164(&local, p5);
    local.unk_1E = *p4;

    func_0203d4cc(&local, p0);
    func_0203d4c8(&local, p3);
    func_0203d4d0(&local, 1);
    func_0203d668(&data_021c69b4);
    v1 = func_0203d564(&data_021c69b4, &local);

    func_0203d4c8(&local, 0);
    func_0203d4cc(&local, p1);
    func_0203d4d0(&local, 2);
    func_0203d668(&data_021c69b4);
    v2 = func_0203d564(&data_021c69b4, &local);

    func_0203d4cc(&local, p2);
    func_0203d4d0(&local, 3);
    func_0203d668(&data_021c69b4);
    v3 = func_0203d564(&data_021c69b4, &local);

    result = (v1 && v2 && v3) ? 1 : 0;

    func_0203d528(&local);
    return result;
}
