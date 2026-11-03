/* menu_tab: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208be44 @ 0x0208be44, 0x40 bytes, Thumb
 * func_0208be3c @ 0x0208be3c, 0x6 bytes, Thumb
 * func_0208be24 @ 0x0208be24, 0x18 bytes, Thumb
 * func_0208bdf4 @ 0x0208bdf4, 0x30 bytes, Thumb
 * func_0208bdd0 @ 0x0208bdd0, 0x22 bytes, Thumb
 * func_0208bd90 @ 0x0208bd90, 0x40 bytes, Thumb
 * func_0208bd50 @ 0x0208bd50, 0x40 bytes, Thumb
 * func_0208bd18 @ 0x0208bd18, 0x38 bytes, Thumb
 * func_0208bcfc @ 0x0208bcfc, 0x1a bytes, Thumb
 * func_0208bccc @ 0x0208bccc, 0x30 bytes, Thumb
 * func_0208bca4 @ 0x0208bca4, 0x28 bytes, Thumb
 * func_0208bc88 @ 0x0208bc88, 0x1c bytes, Thumb
 * func_0208bc60 @ 0x0208bc60, 0x26 bytes, Thumb
 * func_0208bc30 @ 0x0208bc30, 0x30 bytes, Thumb
 * func_0208bc0c @ 0x0208bc0c, 0x22 bytes, Thumb
 */

typedef struct {
    char pad_00[0x24];
    unsigned char unk_24;
} UnkStruct_0208be44;

typedef struct {
    unsigned char pad_00[32];
    unsigned long unk_20;
} UnkStruct_0208be3c;

typedef struct {
    char pad_00[0xc];
    void *child;
    char pad_10[0x10];
    int unk_20;
} UnkStruct_0208bdf4;

typedef struct UnkStruct_0208bd90 {
    char pad_00[12];
    char sub[20];
    int unk_20;
    char pad_24;
    char unk_25;
} UnkStruct_0208bd90;

struct Func0208bc88_Struct {
    unsigned char pad_00[0x20];
    int unk_20;
    unsigned char pad_24[0x4];
    unsigned char unk_28[1];
};

struct UnkStruct_0208bc60 {
    unsigned char pad_00[0x24];
    unsigned char unk_24;
    unsigned char pad_25[3];
    int unk_28;
};

typedef struct {
    int pad_00;
} UnkStruct_0208bc30;

typedef struct {
    char pad_00[0xC];
    UnkStruct_0208bc30 unk_0C;
    char pad_10[0x10];
    int unk_20;
} UnkStruct_0208bc30_2;

typedef struct {
    char pad_00[0xC];
    int sub;
} UnkStruct_0208bc0c;

extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern void func_020a7e64(void);
extern int func_020a7e44(void);
extern int func_020a812c(void);
extern void func_020a7e70(void);
extern void func_020a7dec(void);
extern int func_0208bf48(void *);
extern void func_0208a1f0(void *ptr, void *arg2);
extern void func_0208a1ec(void *ptr, int arg2);
extern void *func_0208a144(void *ptr);
extern char data_020d5c3c;
extern void func_0208a0c8(void *);
extern int func_0208a160(void *);
void func_0208a158(char *);
extern int func_0203e1f8(void);
extern void func_0206f5b0(void);
extern int func_0208be84(void *, int);
extern int func_0203e204(void);
extern void func_0208c630(void *param1, int param2);
extern void func_0200467c(int param1);
extern int func_0208c610(void *ptr);
extern int func_0206f56c(void);
extern int func_0208c620(void *);
extern int func_0203e1ec(void);
extern char data_020d5c44[];

void func_0208bdf4(void *p);
void func_0208bd90(UnkStruct_0208bd90 *obj);
void func_0208bd18(void *param0);
void func_0208bccc(void *arg0);
void func_0208bc88(struct Func0208bc88_Struct *obj);
void func_0208bc30(UnkStruct_0208bc30_2 *s);

void func_0208be44(UnkStruct_0208be44 *s)
{
    if (s->unk_24 == 0) {
        return;
    }
    if (func_020a7e50()) {
        if (func_020a7ffc()) {
            func_020a7e64();
        }
    } else {
        if (func_020a7e44()) {
            if (func_020a812c()) {
                func_020a7e70();
            }
        }
    }
    func_020a7dec();
}

void func_0208be3c(UnkStruct_0208be3c *p)
{
    p->unk_20 = 0;
}

void func_0208be24(int r0)
{
    int r4 = r0;
    if (func_0208bf48((void *) r0) != 0) {
        func_0208bdf4((void *) r4);
    }
}

void func_0208bdf4(void *p)
{
    UnkStruct_0208bdf4 *self = (UnkStruct_0208bdf4 *) p;

    self->unk_20 = 1;
    func_0208a1f0(&self->child, &data_020d5c3c);
    func_0208a1ec(&self->child, 1);
    func_0208a144(&self->child);
}

void func_0208bdd0(void *param)
{
    void *ptr;
    int result;

    ptr = (void *) ((char *) param + 0xc);
    func_0208a0c8(ptr);
    ptr = (void *) ((char *) param + 0xc);
    result = func_0208a160(ptr);
    if (result != 0) {
        func_0208bd90((UnkStruct_0208bd90 *) param);
    }
}

void func_0208bd90(UnkStruct_0208bd90 *obj)
{
    obj->unk_20 = 2;
    obj->unk_25 = 0;
    func_0208a1f0((void *) obj->sub, (void *) ((int) ((int *) data_020d5c44)));
    func_0208a1ec((void *) obj->sub, 1);
    func_0208a144((void *) obj->sub);
    func_0208a158(obj->sub);
}

void func_0208bd50(void *param)
{
    if (func_0203e1f8()) {
        func_0206f5b0();
        func_0208bd18(param);
    } else if (func_0208bf48(param) == 0) {
        func_0208bc30((UnkStruct_0208bc30_2 *) param);
    } else if (func_0208be84(param, 0) != 0) {
        func_0203e204();
    }
}

void func_0208bd18(void *param0)
{
    unsigned char *r4;
    unsigned char temp;

    r4 = (unsigned char *) param0;
    *(unsigned int *) (r4 + 0x20) = 3;
    func_0208c630(r4 + 0x28, 1);
    *(r4 + 0x24) = 1;
    temp = *(r4 + 0x25);
    if (temp != 0) {
        func_020a7e64();
    } else {
        func_020a7e70();
    }
    func_0200467c(0x4a);
}

void func_0208bcfc(void *ptr)
{
    void *r4 = ptr;
    if (func_0208c610((char *) ptr + 0x28) != 0) {
        func_0208bccc(r4);
    }
}

void func_0208bccc(void *arg0)
{
    extern void func_0208a1f0(void *, void *);
    extern void func_0208a1ec(void *, int);
    extern void *func_0208a144(void *);
    extern unsigned char data_020d5c4c[];

    *(int *) ((char *) arg0 + 0x20) = 4;
    func_0208a1f0((char *) arg0 + 0xc, data_020d5c4c);
    func_0208a1ec((char *) arg0 + 0xc, 1);
    func_0208a144((char *) arg0 + 0xc);
}

void func_0208bca4(int arg)
{
    int r4;
    int r0;

    r4 = func_0208be84((void *) arg, 1);
    r0 = func_0206f56c();
    if (r4 != 0 || r0 != 0) {
        func_0208bc88((struct Func0208bc88_Struct *) arg);
    }
}

void func_0208bc88(struct Func0208bc88_Struct *obj)
{
    obj->unk_20 = 5;
    func_0208c630(obj->unk_28, 0);
    func_0200467c(0x4b);
}

void func_0208bc60(struct UnkStruct_0208bc60 *param)
{
    if (func_0208c620(&param->unk_28)) {
        func_0203e1ec();
        param->unk_24 = 0;
        func_0208bd90((UnkStruct_0208bd90 *) param);
    }
}

void func_0208bc30(UnkStruct_0208bc30_2 *s)
{
    s->unk_20 = 6;
    func_0208a1f0((void *) (&s->unk_0C), data_020d5c44);
    func_0208a1ec((void *) (&s->unk_0C), 1);
    func_0208a144((void *) (&s->unk_0C));
}

void func_0208bc0c(UnkStruct_0208bc0c *obj)
{
    func_0208a0c8(&obj->sub);
    if (func_0208a160(&obj->sub)) {
        func_0208be3c((UnkStruct_0208be3c *) obj);
    }
}
