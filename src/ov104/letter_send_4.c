/* letter_send_4: 5 functions, module ov104
 * mwccarm 1.2/base -O4,s
 * func_ov104_0229d304 @ 0x0229d304, 0x74 bytes, Thumb
 * func_ov104_0229d2b4 @ 0x0229d2b4, 0x50 bytes, Thumb
 * func_ov104_0229d250 @ 0x0229d250, 0x64 bytes, Thumb
 * func_ov104_0229d1ec @ 0x0229d1ec, 0x64 bytes, Thumb
 * func_ov104_0229d1b8 @ 0x0229d1b8, 0x34 bytes, Thumb
 */

typedef struct {
    char pad_00[0x64];
} ObjB;

typedef struct {
    char pad_00[1];
} ObjA;

typedef struct {
    char pad_00[0xBD];
    unsigned char flag;
    char pad_BE[0x23E2];
    ObjB objB;
    ObjA objA;
} UnkStruct_0229d1ec;

struct UnkStruct_0229d1b8 {
    char pad_00[0x24a0];
    int unk_24A0;
};

extern int func_ov104_0229c364(void *, int);
extern void func_ov104_0229c344(void *, int);
extern int func_ov104_0229d3ac(void *);
extern int func_ov104_0229d39c(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a05c(void *, int, int, int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern int func_ov002_0220a08c(void *p, int a, int b, int c);
extern int func_ov002_022090e4(unsigned char *, int);
extern void func_0208e4c0(unsigned char *, int);
extern void func_ov002_0220a374(ObjB *a, int b);

void func_ov104_0229d304(void *param)
{
    int v1, v2;
    if (func_ov104_0229c364(param, 8) != 0) {
        v1 = func_ov104_0229d3ac(param);
        v2 = func_ov104_0229d39c(param);
        func_ov002_0220a0b4((char *) param + 0x24a0, v1, v2);
        func_ov104_0229c344(param, 8);
    } else {
        v1 = func_ov104_0229d3ac(param);
        v2 = func_ov104_0229d39c(param);
        func_ov002_0220a05c((char *) param + 0x24a0, v1, v2, 3, 1);
        *(unsigned char *) ((char *) param + 0xbb) = *(unsigned char *) ((char *) param + 0x8d);
        func_ov002_02208098((void *) (param), 13);
    }
}

void func_ov104_0229d2b4(unsigned char *self)
{
    int a = func_ov002_02208ae4(self + 0x2504);
    int b = func_ov002_02208ad8(self + 0x2504, *(unsigned char *) (self + 0xbd));
    func_ov002_0220a08c(self + 0x24a0, a, b, 2);
    *(unsigned char *) (self + 0xbb) = *(unsigned char *) (self + 0x8d);
    func_ov002_02208098((void *) (self), 13);
}

void func_ov104_0229d250(unsigned char *p)
{
    int a;
    int b;

    p[0xBC] = 4;
    p[0xBD] = func_ov002_022090e4(p + 0x2504, 1);
    a = func_ov002_02208ae4((void *) (p + 0x2504));
    b = func_ov002_02208ad8((void *) (p + 0x2504), p[0xBD]);
    func_ov002_0220a0b4((void *) (p + 0x24A0), a, b);
    func_0208e4c0(p + 0x24A0, 8);
    func_ov002_02208098((void *) (p), 23);
}

void func_ov104_0229d1ec(UnkStruct_0229d1ec *self)
{
    int r4, r2;
    if (func_ov104_0229c364(self, 0x8000) != 0) {
        self->flag = 1;
    } else {
        self->flag = 0;
    }
    r4 = func_ov002_02208ae4((void *) (&self->objA));
    r2 = func_ov002_02208ad8((void *) (&self->objA), self->flag);
    func_ov002_0220a0b4((void *) (&self->objB), r4, r2);
    func_ov002_0220a374(&self->objB, 7);
}

void func_ov104_0229d1b8(struct UnkStruct_0229d1b8 *self)
{
    int v1 = func_ov104_0229d3ac((void *) self);
    int v2 = func_ov104_0229d39c((void *) self);
    func_ov002_0220a0b4(&self->unk_24A0, v1, v2);
    func_ov002_0220a374((ObjB *) (&self->unk_24A0), 1);
}
