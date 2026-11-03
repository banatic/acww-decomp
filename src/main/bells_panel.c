/* bells_panel: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208b824 @ 0x0208b824, 0x18 bytes, Thumb
 * func_0208b800 @ 0x0208b800, 0x22 bytes, Thumb
 * func_0208b79c @ 0x0208b79c, 0x64 bytes, Thumb
 * func_0208b77c @ 0x0208b77c, 0x20 bytes, Thumb
 * func_0208b748 @ 0x0208b748, 0x34 bytes, Thumb
 * func_0208b720 @ 0x0208b720, 0x26 bytes, Thumb
 * func_0208b6ec @ 0x0208b6ec, 0x34 bytes, Thumb
 * func_0208b658 @ 0x0208b658, 0x94 bytes, Thumb
 * func_0208b648 @ 0x0208b648, 0xe bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned int unk_7C;
    unsigned char unk_80;
    unsigned char unk_81;
    unsigned char unk_82;
} ExampleStruct;

typedef struct UnkStruct_0208b79c {
    char pad_00[0x38];
    int unk_38;
    char pad_3C[0x40];
    int unk_7C;
    char pad_80[0x2];
    unsigned char unk_82;
} UnkStruct_0208b79c;

typedef struct UnkStruct_0208b77c {
    char pad_00[0x7c];
    void *unk_7C;
} UnkStruct_0208b77c;

struct UnkStruct_0208b6ec {
    char pad_00[0x24];
    int unk_24;
};

struct UnkStruct_0208b658 {
    char pad_00[0x28];
    unsigned int unk_28;
    unsigned int unk_2C;
    int unk_30;
    int unk_34;
};

struct UnkStruct_0208b648 {
    char pad_00[0x28];
    unsigned int unk_28;
    unsigned int unk_2C;
    unsigned int unk_30;
    unsigned int unk_34;
};

extern void func_020a8fb8(void *);
extern void func_02051624(int);
extern void func_02051694(int);
extern int func_020e88dc(int *p, int a, int b);
extern int func_020b45d0(void *p1, void *p2, int p3, int p4, int p5, int p6);
extern void func_0200452c(void);
extern void func_0200453c(void);
extern void func_0200467c(int);
extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098cf8(int, int);
extern int func_0206f854(void);
extern int func_0206fd10(void);
extern int FX_MulFunc(int a, int b);
extern int func_0206fd04(void);
extern int func_02039860(void);
extern int func_020e8bb0(void *a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void func_0208b77c(UnkStruct_0208b77c *a);
int func_0208b720(void *receiver);
void func_0208b648(struct UnkStruct_0208b648 *s);

void func_0208b824(void *arg0)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (*(unsigned int *) ((char *) arg0 + 0x38))) != 0) {
        func_020a8fb8(condition_value0);
        *(unsigned int *) ((char *) arg0 + 0x38) = 0;
    }
}

void func_0208b800(ExampleStruct *self)
{
    self->unk_7C = func_0208b720(self);
    func_0208b77c((UnkStruct_0208b77c *) self);
    self->unk_81 = 0;
    self->unk_82 = 0;
}

int func_0208b79c(UnkStruct_0208b79c *s)
{
    int ret = 0;
    int call;
    int diff;
    int q;
    if (s->unk_82 == 0) {
        call = func_0208b720(s);
        if (s->unk_7C != call) {
            diff = call - s->unk_7C;
            if (diff < 0) {
                diff = -diff;
            }
            q = ((diff / 6) + 50) / 10;
            func_020e88dc(&s->unk_7C, call, q * 10 + 7);
            func_0208b77c((UnkStruct_0208b77c *) s);
            if (s->unk_38 != 0) {
                func_02051624(s->unk_38);
                func_02051694(s->unk_38);
            }
            ret = 1;
        }
    }
    return ret;
}

void func_0208b77c(UnkStruct_0208b77c *a)
{
    func_020b45d0((char *) a + 0x3c, a->unk_7C, 7, 0, 0, 1);
}

void func_0208b748(unsigned char *param0, int param1)
{
    unsigned char *r5;
    int r4;

    r5 = param0;
    r4 = param1;

    if (param0[0x81] != 0) {
        if (r4 == 0) {
            func_0200452c();
            func_0200467c(0x2e);
        }
    } else {
        if (r4 != 0) {
            func_0200453c();
        }
    }

    r5[0x81] = r4;
}

int func_0208b720(void *receiver)
{
    int a = func_020984e8();
    int result = 0;
    if (a != 0) {
        int b = func_02099734(a);
        int c = func_02098cf8(b, 1);
        int d = func_0206f854();
        result = c + d;
    }
    return result;
}

void func_0208b6ec(struct UnkStruct_0208b6ec *param)
{
    int v1;
    int v2;
    int v3;

    v1 = func_0206fd10();
    v2 = FX_MulFunc(0, v1);
    v3 = FX_MulFunc(0x000c0000, 0x00001000 - v1);
    param->unk_24 = (v2 + v3) >> 12;
}

void func_0208b658(struct UnkStruct_0208b658 *self)
{
    unsigned int val;

    if (func_0206fd04() != 0) {
        if (func_02039860() != 0) {
            val = 0x28000;
        } else {
            val = 0;
        }
        self->unk_30 += 0xa00;
        self->unk_30 = (self->unk_30 < 0x2300) ? 0x2300 : (self->unk_30 > 0x5000) ? 0x5000 : self->unk_30;
        if (val != self->unk_2C) {
            if (self->unk_34 >= 0) {
                self->unk_34++;
                if (self->unk_34 <= 5) {
                    goto l_done;
                }
            }
            self->unk_2C = val;
            self->unk_34 = 0;
        l_done:;
        } else {
            self->unk_34 = 0;
        }
        func_020e8bb0((char *) self + 0x28, self->unk_2C, 0x600, self->unk_30, 0x2300);
    } else {
        func_0208b648((struct UnkStruct_0208b648 *) self);
    }
}

void func_0208b648(struct UnkStruct_0208b648 *s)
{
    s->unk_28 = 0;
    s->unk_2C = 0;
    s->unk_34 = -1;
    s->unk_30 = 0;
}
