/* func_02050394 @ 0x02050394, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int w[12];
} Mtx;
typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x8c - 0x44];
    Vec3 unk_8C;
    char pad_98[0x15c - 0x98];
    short unk_15C, unk_15E, unk_160;
} UnkStruct_02050394_2;
typedef struct {
    char pad_00[8];
    int unk_08;
} UnkStruct_02050394;

extern char data_021fbe48[];

extern int func_0203f8d0(Vec3 *d, Vec3 *s);
extern void func_020e96c8(char *g, int x, int y, int z);
extern void func_020e9774(char *g, int a);
extern void func_020e97a4(char *g, int a, int b, int c);
extern void func_020e9744(char *g, int a);
extern void func_020e9714(char *g, int a);

void func_02050394(UnkStruct_02050394 *a0, UnkStruct_02050394_2 *self)
{
    Vec3 a;
    Vec3 b;
    Vec3 *q;
    char *m;
    int k;
    int mode;
    int r;

    m = (char *) self + 0x98;
    k = self->unk_40;
    q = &self->unk_8C;
    a.x = self->unk_8C.x;
    a.y = q->y;
    a.z = q->z;
    mode = a0->unk_08;
    if (mode == 0) {
        r = func_0203f8d0(&b, &a);
    } else if (mode == 1) {
        r = 0;
        b.x = a.x;
        b.y = a.y;
        b.z = a.z;
    }
    func_020e96c8(data_021fbe48, b.x, b.y, b.z);
    func_020e9774(data_021fbe48, r);
    if (k != 0xf) {
        func_020e97a4(data_021fbe48, self->unk_15C, self->unk_15E, self->unk_160);
    } else {
        func_020e9744(data_021fbe48, self->unk_15E);
        func_020e9714(data_021fbe48, self->unk_160);
        func_020e9774(data_021fbe48, self->unk_15C);
    }
    m = m + 0x64;
    *(Mtx *) m = *(Mtx *) data_021fbe48;
}
