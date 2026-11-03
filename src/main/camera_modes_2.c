/* camera_modes_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203ba60 @ 0x0203ba60, 0x12c bytes, Thumb
 * func_0203b994 @ 0x0203b994, 0xcc bytes, Thumb
 * func_0203b868 @ 0x0203b868, 0x12c bytes, Thumb
 * func_0203b7d0 @ 0x0203b7d0, 0x98 bytes, Thumb
 * func_0203b684 @ 0x0203b684, 0x14c bytes, Thumb
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

typedef struct {
    char pad_00[0xfc];
    short unk_FC;
    short unk_FE;
    int unk_100;
    int unk_104;
    int unk_108;
    int unk_10C;
    int unk_110;
    int unk_114;
    int unk_118;
    short unk_11C;
    short unk_11E;
    int unk_120;
    int unk_124;
    int unk_128;
    int unk_12C;
    int unk_130;
    int unk_134;
    int unk_138;
    int unk_13C;
    int unk_140;
    int unk_144;
    char pad_148[0x168 - 0x148];
    int unk_168;
    int unk_16C;
    int unk_170;
    char pad_174[0x1f4 - 0x174];
    char unk_1F4;
    char pad_1F5[0x204 - 0x1f5];
    int unk_204;
    int unk_208;
    int unk_20C;
    int unk_210;
    int unk_214;
    int unk_218;
} UnkStruct_0203b868;

typedef struct {
    unsigned char pad_00[0x1f4];
    unsigned char flag;
    unsigned char pad_1F5[0xf];
    int unk_204;
    int unk_208;
    int unk_20C;
    int unk_210;
    int unk_214;
    int unk_218;
} UnkStruct_0203b7d0;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} GlobStruct;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0203b7d0_2;

typedef struct {
    char pad_00[0x110];
    int unk_110, unk_114, unk_118;
    char pad_11C[0x1f4 - 0x11c];
    unsigned char unk_1F4;
    char pad_1F5[0x1fc - 0x1f5];
    int unk_1FC;
} UnkStruct_0203b684;

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
extern void func_0203ad58(void);
extern void func_0203c99c(void *, int);
extern void func_0203ad68(void);
extern UnkStruct_0203b7d0_2 *func_0203c59c(UnkStruct_0203b7d0 *self);
extern int func_0203ad88(void);
extern void func_020ea78c(Vec3 *v, short a);
extern void func_020ea6e0(Vec3 *v, int a);
extern void func_01ffd070(Vec3 *dst, Vec3 *a, Vec3 *b);
extern int func_0206fd34(void);
extern int func_ov068_0226dabc(void *self);
extern void func_0203bcc4(void *self, Vec3 *a, Vec3 *b);

int func_0203b7d0(UnkStruct_0203b7d0 *self);

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

void func_0203b994(int p0)
{
    *(unsigned char *) ((char *) (p0) + (500)) = 1;
    *(unsigned short *) ((char *) (p0) + (284)) = *(short *) ((char *) (p0) + (252));
    *(unsigned short *) ((char *) (p0) + (286)) = *(short *) ((char *) (p0) + (254));
    *(int *) ((char *) (p0) + (288)) = *(int *) ((char *) (p0) + (256));
    *(int *) ((char *) (p0) + (292)) = *(int *) ((char *) (p0) + (260));
    *(int *) ((char *) (p0) + (296)) = *(int *) ((char *) (p0) + (264));
    *(int *) ((char *) (p0) + (300)) = *(int *) ((char *) (p0) + (268));
    *(int *) ((char *) (p0) + (304)) = *(int *) ((char *) (p0) + (272));
    *(int *) ((char *) (p0) + (308)) = *(int *) ((char *) (p0) + (276));
    *(int *) ((char *) (p0) + (312)) = *(int *) ((char *) (p0) + (280));
    *(int *) ((char *) (p0) + (316)) = *(int *) ((char *) (p0) + (360));
    *(int *) ((char *) (p0) + (320)) = *(int *) ((char *) (p0) + (364));
    *(int *) ((char *) (p0) + (324)) = *(int *) ((char *) (p0) + (368));
    func_0203b7d0((UnkStruct_0203b7d0 *) p0);
}

void func_0203b868(UnkStruct_0203b868 *p)
{
    int *q110;
    int *q114;
    int *q118;
    int *q168;
    int *q16c;
    int *q170;

    p->unk_1F4 = 0;
    func_0203b7d0((UnkStruct_0203b7d0 *) p);
    p->unk_FC = p->unk_11C;
    p->unk_FE = p->unk_11E;
    p->unk_100 = p->unk_120;
    p->unk_104 = p->unk_124;
    p->unk_108 = p->unk_128;
    p->unk_10C = p->unk_12C;
    q110 = &p->unk_110;
    *q110 = p->unk_130;
    q114 = &p->unk_114;
    *q114 = p->unk_134;
    q118 = &p->unk_118;
    *q118 = p->unk_138;
    q168 = &p->unk_168;
    *q168 = p->unk_13C;
    q16c = &p->unk_16C;
    *q16c = p->unk_140;
    q170 = &p->unk_170;
    *q170 = p->unk_144;
    p->unk_204 = *q110;
    p->unk_208 = *q114;
    p->unk_20C = *q118;
    p->unk_210 = *q168;
    p->unk_214 = *q16c;
    p->unk_218 = *q170;
    func_0203ad58();
    func_0203c99c(p, 2);
}

int func_0203b7d0(UnkStruct_0203b7d0 *self)
{
    int local[3];
    UnkStruct_0203b7d0_2 *p;

    if (self->flag == 0) {
        func_01ffcbb0((void *) local, (void *) self);
        self->unk_204 = local[0];
        self->unk_208 = local[1];
        self->unk_20C = local[2];
        p = func_0203c59c(self);
        self->unk_210 = p->a;
        self->unk_214 = p->b;
        self->unk_218 = p->c;
        func_0203ad68();
    } else {
        if ((*(GlobStruct * *) &data_021f6948)->unk_04 == 0) {
            func_0203caa4((void *) self, 0xf, 0);
        } else {
            func_0203caa4((void *) self, 0xe, 0);
        }
        func_0203c99c((void *) self, 1);
        func_0203ad58();
    }
    return 1;
}

void func_0203b684(UnkStruct_0203b684 *self)
{
    volatile int A[3];
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Vec3 d;
    Vec3 e;
    Vec3 *p;
    int i, j, k;
    int z0;

    A[0] = data_021fbee8.x;
    A[1] = data_021fbee8.y;
    A[2] = data_021fbee8.z;
    p = func_02095794(4);
    if (p != 0) {
        A[0] = p->x;
        A[1] = p->y;
        A[2] = p->z;
    }
    if (self->unk_1F4 == 0) {
        func_0203be6c(self);
        func_01ffcbb0(&a, self);
        p = (Vec3 *) func_0203c59c((UnkStruct_0203b7d0 *) self);
        b.x = p->x;
        b.y = p->y;
        b.z = p->z;
        if (func_0203ad88() != 0) {
            z0 = func_0203c548(self);
            c.x = 0;
            c.y = 0;
            c.z = z0;
            func_020ea78c(&c, (short) -(int) func_0203c57c(self));
            func_020ea6e0(&c, (int) func_0203c568(self));
            func_01ffd070(&d, &a, &c);
            b.x = d.x;
            b.y = d.y;
            b.z = d.z;
        }
        a.y = a.y + (0x1000 - func_0206fd34()) * 15;
        b.y = b.y + (0x1000 - func_0206fd34()) * 2;
        if (self->unk_1FC == 9) {
            a.y = a.y + func_ov068_0226dabc(self);
        }
        func_0203bcc4(self, &a, &b);
    } else {
        self->unk_110 = A[0];
        self->unk_114 = A[1];
        self->unk_118 = A[2];
        func_0203be6c(self);
        func_01ffcbb0(&e, self);
        i = (int) func_0203c57c(self);
        j = (int) func_0203c568(self);
        k = func_0203c548(self);
        func_0203bd84(self, &e, i, j, k);
    }
}
