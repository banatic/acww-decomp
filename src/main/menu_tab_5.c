/* menu_tab_5: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208c1dc @ 0x0208c1dc, 0x40 bytes, Thumb
 * func_0208c1ac @ 0x0208c1ac, 0x30 bytes, Thumb
 * func_0208c178 @ 0x0208c178, 0x34 bytes, Thumb
 * func_0208c0f8 @ 0x0208c0f8, 0x80 bytes, Thumb
 */

struct Sub1 {
    char data[20];
};

struct Sub2 {
    char data[1];
};

struct UnkStruct_0208c1dc {
    void *vtbl;
    char pad_04[8];
    struct Sub1 sub1;
    int unk_20;
    char unk_24;
    char unk_25;
    char unk_26;
    char pad_27;
    struct Sub2 sub2;
};

typedef struct UnkStruct_0208c1ac UnkStruct_0208c1ac;

struct UnkStruct_0208c1ac {
    unsigned int unk_00;
    unsigned char pad_04[8];
    unsigned int unk_0C;
    unsigned char pad_10[0x18];
    unsigned int unk_28;
};

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x08];
    void *unk_0C;
    unsigned char pad_10[0x18];
    void *unk_28;
} UnkStruct_0208c178;

typedef struct {
    char pad_00[0xc];
    char unk_0C[0x20 - 0xc];
    unsigned int unk_20;
} UnkStruct_0208c0f8;

extern void func_0208af30(void *);
extern void func_0208a1f8(void *);
extern void *func_0208c834(void *);
extern void func_0208c008(UnkStruct_0208c1ac *self);
extern void *func_0208c804(void *obj);
extern void func_0208a1f4(void *obj);
extern void func_0208af00(UnkStruct_0208c1ac *self);
extern unsigned char data_020e2234[];
extern void func_020edb3c(void *arg);
extern void *func_0208a1d0(void *p);
extern int func_0208a1b0(void *p, int x);
extern int func_0208a198(void *p, int x);
extern int func_0208aef0(UnkStruct_0208c0f8 *p);
extern int func_0208aeec(UnkStruct_0208c0f8 *p);
extern void func_02088df8(int a0, void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);

struct UnkStruct_0208c1dc *func_0208c1dc(struct UnkStruct_0208c1dc *p)
{
    func_0208af30(p);
    p->vtbl = (void *) ((char *) data_020e2234);
    func_0208a1f8(&p->sub1);
    p->unk_20 = 0;
    p->unk_24 = 0;
    p->unk_25 = 0;
    p->unk_26 = 0;
    func_0208c834(&p->sub2);
    return p;
}

UnkStruct_0208c1ac *func_0208c1ac(UnkStruct_0208c1ac *self)
{
    self->unk_00 = (unsigned int) data_020e2234;
    func_0208c008(self);
    func_0208c804(&self->unk_28);
    func_0208a1f4(&self->unk_0C);
    func_0208af00(self);
    return self;
}

UnkStruct_0208c178 *func_0208c178(UnkStruct_0208c178 *p)
{
    p->unk_00 = (void *) ((unsigned char *) data_020e2234);
    func_0208c008((UnkStruct_0208c1ac *) p);
    func_0208c804(&p->unk_28);
    func_0208a1f4(&p->unk_0C);
    func_0208af00((UnkStruct_0208c1ac *) p);
    func_020edb3c(p);
    return p;
}

void func_0208c0f8(UnkStruct_0208c0f8 *s)
{
    void *saved;
    int v1, v2, v3, v4;
    int choice;

    if (s->unk_20 == 0) {
        return;
    }
    saved = func_0208a1d0((void *) &s->unk_0C);
    if (saved == 0) {
        return;
    }
    v1 = func_0208a1b0((void *) &s->unk_0C, -1);
    v2 = func_0208a198((void *) &s->unk_0C, -1);
    v3 = func_0208aef0(s);
    v4 = func_0208aeec(s);
    if ((s->unk_20 - 3) <= 2) {
        choice = 6;
    } else {
        choice = 5;
    }
    func_02088df8(0, saved, v3 + v1, v4 + v2, choice, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
