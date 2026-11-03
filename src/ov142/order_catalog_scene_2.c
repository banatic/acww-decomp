/* order_catalog_scene_2: 14 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_0229bd70 @ 0x0229bd70, 0x4 bytes, Thumb
 * func_ov142_0229bd6c @ 0x0229bd6c, 0x4 bytes, Thumb
 * func_ov142_0229bd5c @ 0x0229bd5c, 0x10 bytes, Thumb
 * func_ov142_0229bcfc @ 0x0229bcfc, 0x60 bytes, Thumb
 * func_ov142_0229bc9c @ 0x0229bc9c, 0x60 bytes, Thumb
 * func_ov142_0229bc64 @ 0x0229bc64, 0x38 bytes, Thumb
 * func_ov142_0229bc34 @ 0x0229bc34, 0x30 bytes, Thumb
 * func_ov142_0229bbf4 @ 0x0229bbf4, 0x40 bytes, Thumb
 * func_ov142_0229bbc4 @ 0x0229bbc4, 0x2e bytes, Thumb
 * func_ov142_0229bb84 @ 0x0229bb84, 0x40 bytes, Thumb
 * func_ov142_0229bb54 @ 0x0229bb54, 0x2e bytes, Thumb
 * func_ov142_0229bb08 @ 0x0229bb08, 0x4a bytes, Thumb
 * func_ov142_0229ba64 @ 0x0229ba64, 0xa4 bytes, Thumb
 * func_ov142_0229ba18 @ 0x0229ba18, 0x4c bytes, Thumb
 */

typedef struct {
    char pad_00[0x98];
    int value;
} UnkStruct_0229bbc4;

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
} UnkStruct_0229bb54;

typedef struct {
    unsigned char pad_00[0xb6];
    unsigned short x1;
    unsigned char pad_B8[4];
    unsigned char x2;
    unsigned char pad_BD[4];
    unsigned char x3;
    unsigned char x4;
    unsigned char pad_C3[1];
    unsigned short c4[9];
    unsigned short d6[9];
    unsigned char pad_E8[0x184e - 0xd6 - 18];
    unsigned short a3[9];
} UnkStruct_0229ba64;

extern void func_020ee470(void *argument0);
extern void func_ov142_0229b928(void);
extern void func_ov142_0229b874(void *p);
extern void func_ov142_0229ab80(void *p, int a);
extern void func_ov142_0229b804(void *p);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int a);
extern int func_ov002_0220ab84(void *p, int a);
extern void func_ov002_02208090(void *p, int a);
extern int func_ov142_02299668(void *self, int a);
extern void func_ov142_02299658(void *self, int a);
extern void func_ov142_0229ac58(void *self, int a, int b, int c, int d, int e);
extern void func_ov142_0229abfc(void *object);
extern int func_ov002_02207f48(void *self, int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov142_0229b214(void *self);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int c);
extern void func_ov002_02207eb4(int *, int, int);
extern int func_ov002_0220a924(int *, int);
extern void func_ov142_0229b1b8(void *obj);
extern int func_ov002_02207f60(void *obj);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov142_02299ab8(void *p);
extern int func_ov142_0229a0f8(UnkStruct_0229ba64 *, int, int);
extern void func_ov142_0229a9bc(UnkStruct_0229ba64 *);
extern void func_ov142_0229a988(UnkStruct_0229ba64 *);
extern void func_ov142_0229a954(UnkStruct_0229ba64 *);
extern void func_ov142_0229a91c(UnkStruct_0229ba64 *);
extern void func_ov142_0229a8e8(UnkStruct_0229ba64 *);
extern void func_ov142_0229a8b4(UnkStruct_0229ba64 *);
extern void func_ov142_0229a7e0(UnkStruct_0229ba64 *);
extern void func_ov142_0229a880(UnkStruct_0229ba64 *);
extern void func_ov142_0229a84c(UnkStruct_0229ba64 *);
extern void func_ov002_0220a580(void *);
extern void func_ov142_0229ae60(void *);
extern void func_020b9ccc(void *);
extern void func_ov002_0220af74(void *);

void func_ov142_0229bb08(void *p);

int func_ov142_0229bd70(void)
{
    return 1;
}

int func_ov142_0229bd6c(void)
{
    return 1;
}

int func_ov142_0229bd5c(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov142_0229bcfc(void *p)
{
    func_ov142_0229b928();
    func_ov142_0229b874(p);
    func_ov142_0229ab80(p, 0);
    func_ov142_0229b804(p);
    func_ov002_02207f20(p, 0xa, 4, 0, 0x18);
    func_02002708(6);
    func_02002708(4);
    func_ov142_0229bb08(p);
    func_ov002_0220ab84((char *) p + 0x194, 0x65);
    func_ov002_02208090(p, 1);
}

void func_ov142_0229bc9c(void *self)
{
    if (func_ov142_02299668(self, 1) == 0) {
        func_ov142_02299658(self, 1);
        func_ov142_0229ac58(self, 0xb8, 0x16d, 4, 0xf, 0);
        func_ov142_0229abfc(self);
    }
    if (func_ov002_02207f48(self, 0) != 0) {
        func_ov002_022080a0((void *) (self), 2);
        func_ov142_0229b214(self);
    }
    func_ov142_0229bb08(self);
}

void func_ov142_0229bc64(void *arg)
{
    func_ov092_02299324(func_020ee45c(arg), 0x44, 1);
    func_ov002_02207f04(arg, 0xa, 0, 0, 0x18);
    func_ov142_0229bb08(arg);
    func_ov002_02208090(arg, 3);
}

void func_ov142_0229bc34(int param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov142_0229bb08((void *) param);
    }
}

void func_ov142_0229bbf4(int *param)
{
    if (func_ov002_02207f3c((int) param, -1)) {
        func_ov002_02208090((void *) param, 5);
        func_ov002_02207eb4(param, 0, 0);
        func_ov002_0220a924(param + 101, 0x22);
    }
    param[38] = func_ov002_02207f60((void *) param);
}

void func_ov142_0229bbc4(UnkStruct_0229bbc4 *obj)
{
    if (func_ov002_02207f48(obj, -1) != 0) {
        func_ov142_0229b1b8(obj);
        func_ov002_022080a0((void *) (obj), 2);
    }
    obj->value = func_ov002_02207f60(obj);
}

void func_ov142_0229bb84(void *p)
{
    if (func_ov002_02207f3c((int) p, -1) != 0) {
        func_ov002_02208090(p, 7);
        func_ov002_02207eb4((int *) p, 0, 0);
        func_ov002_0220ab84((char *) p + 0x194, 0x65);
    }
    *(int *) ((char *) p + 0x98) = func_ov002_02207f60(p);
}

void func_ov142_0229bb54(UnkStruct_0229bb54 *p)
{
    if (func_ov002_02207f48((void *) p, -1)) {
        func_ov142_0229b214((void *) p);
        func_ov002_022080a0((void *) (p), 2);
    }
    p->unk_98 = func_ov002_02207f60((void *) p);
}

void func_ov142_0229bb08(void *p)
{
    int *q;
    int v;
    func_ov002_02207e80(p, 6, 0, 0);
    q = (int *) ((char *) p + 0x9c);
    v = *q;
    func_ov002_02207e80(p, 4, 0, 0x20 - v);
    *(int *) ((char *) p + 0x94) = func_ov002_02207f60(p);
    *(int *) ((char *) p + 0x98) = *(int *) ((char *) p + 0x94);
    func_ov142_02299ab8(p);
}

void func_ov142_0229ba64(UnkStruct_0229ba64 *p)
{
    int i;

    for (i = 0; i < 9; i++) {
        p->c4[i] = 0;
        p->d6[i] = 0;
    }

    for (i = 0; i < 9; i++) {
        p->a3[i] = 0xfff1;
    }

    p->x1 = 0;
    p->x2 = 9;
    p->x3 = 3;
    p->x4 = 0;

    func_ov142_0229a0f8(p, 9, -1);
    func_ov142_0229a9bc(p);
    func_ov142_0229a988(p);
    func_ov142_0229a954(p);
    func_ov142_0229a91c(p);
    func_ov142_0229a8e8(p);
    func_ov142_0229a8b4(p);
    func_ov142_0229a7e0(p);
    func_ov142_0229a880(p);
    func_ov142_0229a84c(p);

    func_ov002_0220a580((char *) p + 0x14c);
}

void func_ov142_0229ba18(void *self)
{
    func_ov142_0229ae60(self);
    func_ov002_0220af74((char *) self + 0x194);
    func_020b9ccc((char *) self + 0x948);
    func_020b9ccc((char *) self + 0x96c);
    func_020b9ccc((char *) self + 0x990);
    func_020b9ccc((char *) self + 0x9b4);
}
