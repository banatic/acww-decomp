/* talk_slider: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aac68 @ 0x020aac68, 0x24 bytes, Thumb
 * func_020aac44 @ 0x020aac44, 0x24 bytes, Thumb
 * func_020aac1c @ 0x020aac1c, 0x28 bytes, Thumb
 * func_020aabe0 @ 0x020aabe0, 0x3a bytes, Thumb
 * func_020aab48 @ 0x020aab48, 0x98 bytes, Thumb
 * func_020aaabc @ 0x020aaabc, 0x8c bytes, Thumb
 * func_020aaa74 @ 0x020aaa74, 0x46 bytes, Thumb
 * func_020aaa54 @ 0x020aaa54, 0x1e bytes, Thumb
 * func_020aaa38 @ 0x020aaa38, 0x1c bytes, Thumb
 * func_020aaa20 @ 0x020aaa20, 0x18 bytes, Thumb
 * func_020aa9fc @ 0x020aa9fc, 0x24 bytes, Thumb
 * func_020aa9c8 @ 0x020aa9c8, 0x32 bytes, Thumb
 * func_020aa9c0 @ 0x020aa9c0, 0x6 bytes, Thumb
 * func_020aa888 @ 0x020aa888, 0x138 bytes, Thumb
 * func_020aa880 @ 0x020aa880, 0x6 bytes, Thumb
 * func_020aa83c @ 0x020aa83c, 0x44 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int pad_00[5];
    void *arr[5];
} StructAAC68;

typedef struct {
    unsigned char pad_00[0x14];
    unsigned int arr[5];
} UnkStruct_020aac44;

typedef struct {
    char pad_00[0x14];
    int arr[5];
} Func020aac1cStruct;

typedef struct {
    char pad_00[0x2c];
    int unk_2C;
    unsigned char unk_30;
} UnkStruct_020aab48;

typedef struct {
    unsigned char pad_00[0x30];
    unsigned char unk_30;
} UnkStruct_020aaabc;

struct func_020aaa74_s {
    int a;
    char pad_04[12];
    int b;
};

typedef struct {
    char pad_00[0x2c];
    int unk_2C;
} UnkStruct_020aaa54;

typedef struct {
    unsigned char pad_00[44];
    unsigned long unk_2C;
} UnkStruct_020aa9c0;

typedef struct UnkStruct_020aa888 {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    u8 pad_14[0x30 - 0x14];
    u8 unk_30;
} UnkStruct_020aa888;

typedef struct {
    unsigned char pad_00[44];
    unsigned long unk_2C;
} UnkStruct_020aa880;

struct UnkStruct_020aa83c {
    char pad_00[8];
    int unk_08;
    char pad_0C[40];
    int unk_34;
};

extern void func_02051694(void *);
extern void func_0205166c(unsigned int, unsigned int);
extern void func_020a8fb8(int arg);
extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern void func_020a7e64(void);
extern int func_020a7e44(void);
extern int func_020a812c(void);
extern void func_020a7e70(void);
extern int func_020a7f5c(void);
extern int func_020a7f34(void);
extern int func_020a7f84(void);
extern void func_0200467c(int cmd);
extern void func_020a7e7c(void);
extern void func_020a7e88(void);
extern int func_020abd44(int);
extern int func_020abd2c(int);
extern int func_020a80c4(int, int, int, int);
extern int func_020a806c(int *, int *);
extern int func_020a7fd4(void);
extern int func_020a8028(int a, int b);
extern int func_020a7f0c(void);
extern int func_020abd98(void *p);
extern int func_020abcfc(void *p);
extern int func_020abd14(void *p);
extern int func_020a7ebc(void);
extern int func_020a7e94(void);
extern int func_020ab504(int);
extern void func_020ab3a8(int, int);

int func_020aaa74(struct func_020aaa74_s *p);
int func_020aaa54(UnkStruct_020aaa54 *p);
int func_020aaa38(void *object);
int func_020aaa20(void *object);
int func_020aa9fc(void *object);
void func_020aa9c0(UnkStruct_020aa9c0 *p);
void func_020aa880(UnkStruct_020aa880 *p);

void func_020aac68(StructAAC68 *s)
{
    unsigned int i;
    for (i = 0; i < 5; i++) {
        if (s->arr[i]) {
            func_02051694(s->arr[i]);
        }
    }
}

void func_020aac44(UnkStruct_020aac44 *p)
{
    unsigned int i;
    unsigned int zero = 0;
    unsigned int val;
    for (i = 0; i < 5; i++) {
        val = p->arr[i];
        if (val) {
            func_0205166c(val, zero);
        }
    }
}

void func_020aac1c(Func020aac1cStruct *s)
{
    unsigned int i;
    for (i = 0; i < 5; i++) {
        if (s->arr[i]) {
            func_020a8fb8(s->arr[i]);
            s->arr[i] = 0;
        }
    }
}

int func_020aabe0(void)
{
    int r4;
    int r0;

    r4 = 0;
    if (func_020a7e50() != 0) {
        if (func_020a7ffc() != 0) {
            func_020a7e64();
            r4 = 1;
        }
    } else {
        if (func_020a7e44() != 0) {
            if (func_020a812c() != 0) {
                func_020a7e70();
                r4 = 1;
            }
        }
    }
    return r4;
}

void func_020aab48(UnkStruct_020aab48 *p)
{
    int a;
    int b;

    if (func_020a7e50()) {
        if (p->unk_2C == 0) {

            if (func_020aa9fc(p)) {
                func_020aa880((UnkStruct_020aa880 *) p);
            }
        } else if (p->unk_2C == 1) {
            if (p->unk_30) {
                func_020aa9c0((UnkStruct_020aa9c0 *) p);
            }
        }
    } else if (func_020a7e44()) {
        if (p->unk_2C == 0) {
            if (!p->unk_30) {
                a = func_020a7f5c();
                b = func_020a7f34();
                if (a || b) {
                    if (a) {
                        func_0200467c(0xb);
                    }
                    func_020aa880((UnkStruct_020aa880 *) p);
                }
            }
        } else if (p->unk_2C == 1) {
            if (func_020a7f84()) {
                func_0200467c(0xb);
                func_020aa9c0((UnkStruct_020aa9c0 *) p);
            }
        }
    }
}

void func_020aaabc(UnkStruct_020aaabc *self)
{
    unsigned char b;
    int flag;
    int res;

    b = self->unk_30;
    if (b) {
        flag = 0;
        res = func_020a7e50();
        if (res) {

            if (func_020aaa38(self)) {
                flag = 1;
            }
        } else {
            if (func_020a7e44() && func_020aaa20((void *) self)) {
                flag = 1;
            }
        }
        if (flag) {
            self->unk_30 = 0;
            func_020a7e7c();
        }
    } else {
        flag = 0;
        res = func_020a7e50();
        if (res) {
            if (func_020aaa74((struct func_020aaa74_s *) self)) {
                flag = 1;
            }
        } else {
            if (func_020a7e44() && func_020aaa54((UnkStruct_020aaa54 *) self)) {
                flag = 1;
            }
        }
        if (flag) {
            self->unk_30 = 1;
            func_020a7e88();
        }
    }
}

int func_020aaa74(struct func_020aaa74_s *p)
{
    int r = 0;
    int v;
    int w;
    int t0;
    int t1;

    v = func_020abd44(p->a);
    w = func_020abd2c(p->a);
    if (func_020a80c4(v - 5, v + 0x15, w, w + 0x10)) {
        func_020a806c(&t0, &t1);
        p->b = t1 - w;
        r = 1;
    }
    return r;
}

int func_020aaa54(UnkStruct_020aaa54 *p)
{
    return p->unk_2C == 0 && func_020a7fd4() != 0;
}

int func_020aaa38(void *object)
{
    int result;
    int ret;

    result = func_020a8028(0, 0);
    if (result == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

int func_020aaa20(void *object)
{
    int result;

    if (func_020a7f0c() == 0) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}

int func_020aa9fc(void *object)
{
    int r4;
    int result;

    r4 = 0;
    result = func_020a80c4(0xb8, 0x100, 0xa0, 0xb0);
    if (result != 0) {
        r4 = 1;
    }
    return r4;
}

int func_020aa9c8(void *param)
{
    int result;
    unsigned char *p;
    int r4;
    int r5;

    r5 = (int) param;
    r4 = 0;
    if (*(int *) (r5 + 0x2c) == 1) {
        if (func_020a7f34() != 0) {
            r4 = 1;
            p = (unsigned char *) (r5 + 0x31);
            *p = (unsigned char) r4;
        } else {
            if (func_020a7fd4() != 0) {
                r4 = 1;
            }
        }
    }
    result = r4;
    return result;
}

void func_020aa9c0(UnkStruct_020aa9c0 *p)
{
    p->unk_2C = 0;
}

void func_020aa888(UnkStruct_020aa888 *self)
{
    int down;
    int speed;
    int upper;
    int crossed;
    int lower;
    int i;
    int up;
    int old;
    int ascending;
    int diff;
    int boundary;
    int pos;
    int x;
    int bottom;
    int top;
    int cur;
    int y;

    if (self->unk_30 != 0 && func_020abd98(self->unk_00) != 0) {
        if (func_020a7e50() != 0) {
            if (func_020a8028((int) (&x), (int) (&y)) != 0) {
                top = func_020abcfc(self->unk_00);
                bottom = func_020abd14(self->unk_00);
                pos = y - self->unk_10;
                if (pos < bottom) {
                    pos = bottom;
                } else if (pos > top) {
                    pos = top;
                }
                self->unk_08 = ((pos - top) << 12) / (bottom - top);
            }
            self->unk_04 = 0;
        } else if (func_020a7e44() != 0) {
            up = func_020a7ebc();
            down = func_020a7e94();
            if (up == 0 && down == 0) {
                self->unk_04 = 0x28;
            } else {
                self->unk_04 += 0x51;
                speed = self->unk_04;
                if (speed < 0) {
                    speed = 0;
                } else if (speed > 0x199) {
                    speed = 0x199;
                }
                self->unk_04 = speed;
            }
            if (up != 0) {
                self->unk_08 += self->unk_04;
            }
            if (down != 0) {
                self->unk_08 -= self->unk_04;
            }
            pos = self->unk_08;
            if (pos < 0) {
                pos = 0;
            } else if (pos > 0x1000) {
                pos = 0x1000;
            }
            self->unk_08 = pos;
        }
    }
    old = self->unk_0C;
    cur = self->unk_08;
    diff = cur - old;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff >= 0x51) {
        ascending = cur > old ? 1 : 0;
        upper = ascending ? cur : old;
        lower = ascending ? old : cur;
        crossed = 0;
        for (i = 0; i < 10; i++) {
            boundary = i * 0x199;
            if (boundary >= lower && boundary < upper) {
                crossed = 1;
                break;
            }
        }
        if (upper == 0x1000) {
            crossed = 1;
        }
        if (crossed != 0) {
            func_0200467c(0x19);
        }
    }
    self->unk_0C = self->unk_08;
}

void func_020aa880(UnkStruct_020aa880 *p)
{
    p->unk_2C = 1;
}

void func_020aa83c(struct UnkStruct_020aa83c *p)
{
    if (p->unk_34 == 0) {
        return;
    }
    if (func_020ab504(p->unk_34) >= 0) {
        return;
    }
    if (func_020a7e50() != 0 && func_020aa9fc((void *) p) != 0) {
        goto final;
    }
    if (func_020a7e44() == 0) {
        return;
    }
    if (func_020aa9c8((void *) p) == 0) {
        return;
    }
final:
    func_020ab3a8(p->unk_34, p->unk_08);
}
