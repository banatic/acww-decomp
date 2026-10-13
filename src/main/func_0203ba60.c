/* func_0203ba60 @ 0x0203ba60, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    unsigned char pad_00[4];
    unsigned char flag;
} FlagStruct;
typedef struct {
    char pad_00[0x110];
    int unk_110, unk_114, unk_118;
    char pad_11C[0x1ec - 0x11c];
    int unk_1EC;
    int unk_1F0;
} UnkStruct_0203ba60;

extern FlagStruct *data_021f6948;
extern Vec3 data_021fbee8;
extern int data_020ca158[][3];

extern Vec3 *func_02095794(int a);
extern int func_020b67d4(void);
extern int func_020b6680(void);
extern int func_020b66d8(void);
extern unsigned char func_020b65c4(void);
extern void func_0203caa4(void *self, int v, void *dst);
extern int func_0203c23c(void *self, void *out);
extern void func_0203bc50(void *self, Vec3 *p);
extern void func_0203be6c(void *self);
extern void func_01ffcbb0(void *dst, void *src);
extern short func_0203c57c(void *self);
extern short func_0203c568(void *self);
extern int func_0203c548(void *self);
extern void func_0203bd84(void *self, void *c, int a, int b, int d);

void func_0203ba60(UnkStruct_0203ba60 *self)
{
    volatile int S[3];
    Vec3 A;
    Vec3 buf;
    Vec3 *p;
    int a, b, d;

    // Retain the ROM's three old-position reads and otherwise dead stores.
    S[0] = self->unk_110;
    S[1] = self->unk_114;
    S[2] = self->unk_118;
    A.x = data_021fbee8.x;
    A.y = data_021fbee8.y;
    A.z = data_021fbee8.z;
    p = func_02095794(4);
    if (p != 0) {
        A.x = p->x;
        A.y = p->y;
        A.z = p->z;
    }
    if (data_021f6948->flag == 0) {
        if (func_020b67d4() != 0 || func_020b6680() != 0 ||
            (func_020b66d8() != 0 && func_020b65c4() != 0x20 && func_020b65c4() != 0x22)) {
            func_0203caa4(self, data_020ca158[self->unk_1F0][self->unk_1EC], 0);
            self->unk_110 = A.x;
            self->unk_114 = A.y;
            self->unk_118 = A.z;
            // The store above also prepares the clamp helper's output.
            if (self->unk_1F0 != 0) {
                func_0203c23c(self, &self->unk_110);
            }
        } else {
            self->unk_110 = A.x;
            self->unk_114 = A.y;
            self->unk_118 = A.z;
            func_0203c23c(self, &self->unk_110);
        }
    } else {
        func_0203bc50(self, &A);
    }
    func_0203be6c(self);
    func_01ffcbb0(&buf, self);
    a = func_0203c57c(self);
    b = func_0203c568(self);
    d = func_0203c548(self);
    func_0203bd84(self, &buf, a, b, d);
}
