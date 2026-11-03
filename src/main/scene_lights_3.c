/* scene_lights_3: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020659b8 @ 0x020659b8, 0xc4 bytes, Thumb
 * func_02065980 @ 0x02065980, 0x38 bytes, Thumb
 * func_02065938 @ 0x02065938, 0x48 bytes, Thumb
 * func_02065914 @ 0x02065914, 0x24 bytes, Thumb
 * func_020658e8 @ 0x020658e8, 0x2c bytes, Thumb
 * func_020658c4 @ 0x020658c4, 0x24 bytes, Thumb
 * func_020658a0 @ 0x020658a0, 0x24 bytes, Thumb
 * func_0206586c @ 0x0206586c, 0x34 bytes, Thumb
 * func_02065858 @ 0x02065858, 0x14 bytes, Thumb
 * func_020656ac @ 0x020656ac, 0x1ac bytes, Thumb
 */

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char pad_04[4];
    unsigned char unk_08;
    unsigned char pad_09[1];
} RecT;

typedef struct {
    unsigned char pad_00[0x50];
    int unk_50;
    int unk_54;
    unsigned char pad_58[0x16a - 0x58];
    unsigned short unk_16A;
    unsigned short unk_16C;
    unsigned short unk_16E;
    unsigned short unk_170;
    unsigned char pad_172[0x178 - 0x172];
    unsigned char unk_178;
} SelfT;

struct Elem {
    char data[0x44];
};

struct Main {
    char pad_00[0x54];
    int count;
    struct Elem elems[1];
};

typedef struct {
    char pad_00[0x124];
    int unk_124;
    unsigned short unk_128;
} UnkStruct_0206586c;

struct UnkStruct_02065858 {
    char pad_00[0x168];
    short unk_168;
};

typedef struct {
    unsigned short r : 5;
    unsigned short g : 5;
    unsigned short b : 5;
    unsigned short a : 1;
} Col;

typedef struct {
    char pad_00[0xf4];
    unsigned char unk_F4;
    char pad_F5[0x168 - 0xf5];
    Col col;
} UnkStruct_020656ac;

extern SelfT *data_021cd864;
extern int func_020b65c4(void);
extern unsigned char data_020ccc48[];
extern RecT data_020ccc7c[];
extern void func_02065a7c(SelfT *self);
extern void func_02065218(void *rec);
extern void func_02064e28(void *rec);
extern void func_020654c8(void *addr);
extern void func_02065450(void *);
extern void func_02064ddc(void *p1, void *p2);
extern void func_020653fc(void *p1, void *p2);
extern char data_0213fee4;
extern void func_020653f0(int);
extern void VEC_Normalize(void *dst, void *src);
extern Col func_020bbf00(int);
extern int func_020b67d4(void);
extern unsigned char data_020e54a8;

void func_020658e8(void *param0, void *param1);
void func_020656ac(UnkStruct_020656ac *self);

int func_020659b8(SelfT *self)
{
    int idx;

    data_021cd864 = self;
    idx = func_020b65c4();
    self->unk_50 = data_020ccc48[idx];

    if (idx == 0x21) {
        self->unk_16A = 0x3e99;
        self->unk_16C = 0x3caa;
        self->unk_16E = 0x494a;
        self->unk_170 = 0x518c;
        self->unk_178 = 0xb;
    } else {
        RecT *rec = &data_020ccc7c[idx];
        self->unk_16A = rec->unk_00;
        self->unk_16C = 0;
        self->unk_16E = rec->unk_02;
        self->unk_170 = 0;
        self->unk_178 = rec->unk_08;
    }

    func_02065a7c(self);

    {
        unsigned char *p = (unsigned char *) self + 0x58;
        int i;
        for (i = 0; i < self->unk_54; i++) {
            func_02065218(p);
            func_02064e28(p);
            p += 0x44;
        }
    }

    func_020654c8((unsigned char *) self + 0x124);

    return 1;
}

int func_02065980(void *arg0)
{
    void *r5;
    int r4;
    void *r6;

    r6 = arg0;
    r5 = (char *) r6 + 0x58;
    r4 = 0;
    while (r4 < *(int *) ((char *) r6 + 0x54)) {
        func_02064e28(r5);
        r5 = (char *) r5 + 0x44;
        r4++;
    }
    func_02065450((char *) r6 + 0x124);
    func_020656ac((UnkStruct_020656ac *) r6);
    return 1;
}

int func_02065938(struct Main *self)
{
    unsigned char buf[0x24];
    int i;
    struct Elem *p;

    func_020658e8(&data_0213fee4, buf);

    p = self->elems;
    for (i = 0; i < self->count; i++) {
        func_02064ddc(p, buf);
        p++;
    }

    func_020653fc((char *) self + 0x124, buf);

    return 1;
}

int func_02065914(int arg)
{
    func_020653f0(arg + 0x124);
    (*(int *) &data_021cd864) = 0;
    return 1;
}

void func_020658e8(void *param0, void *param1)
{
    VEC_Normalize(param0, param1);
    VEC_Normalize((char *) param0 + 0xc, (char *) param1 + 0xc);
    VEC_Normalize((char *) param0 + 0x18, (char *) param1 + 0x18);
}

int func_020658c4(void)
{
    int ret = 15;
    switch (data_020ccc48[func_020b65c4()]) {
        case 2:
        case 3:
            ret = 1;
            break;
    }
    return ret;
}

int func_020658a0(void)
{
    int result = 0xf;
    unsigned char val = data_020ccc48[func_020b65c4()];
    switch (val) {
        case 2:
        case 3:
            result = 1;
            break;
    }
    return result;
}

short func_0206586c(void)
{
    volatile short result = 0;
    if ((*(UnkStruct_0206586c * *) &data_021cd864) && (*(UnkStruct_0206586c * *) &data_021cd864)->unk_124 != 9) {
        result = (*(UnkStruct_0206586c * *) &data_021cd864)->unk_128;
    }
    return result;
}

short func_02065858(void)
{
    return (*(struct UnkStruct_02065858 * *) &data_021cd864)->unk_168;
}

void func_020656ac(UnkStruct_020656ac *self)
{
    Col y, z, x;
    int r, g, b;
    unsigned int ok;
    int k;

    x = func_020bbf00(3);
    y = x;
    z = y;
    if (func_020b67d4() != 0) {
        if (self->unk_F4 != 0) {
            r = z.r + 0xa;
            g = z.g + 0xa;
            b = z.b + 7;
            if (r > 0x1f) {
                z.r = 0x1f;
            } else {
                z.r = r;
            }
            if (g > 0x1f) {
                z.g = 0x1f;
            } else {
                z.g = g;
            }
            if (b > 0x1f) {
                z.b = 0x1f;
            } else {
                z.b = b;
            }
        }
    } else {
        ok = (data_020e54a8 == 1) ? 1 : 0;
        if (ok != 0) {
            k = func_020b65c4();
            switch (k) {
                case 0xb:
                    r = z.r + 0xa;
                    g = z.g + 0xa;
                    b = z.b + 7;
                    if (r > 0x1f) {
                        z.r = 0x1f;
                    } else {
                        z.r = r;
                    }
                    if (g > 0x1f) {
                        z.g = 0x1f;
                    } else {
                        z.g = g;
                    }
                    if (b > 0x1f) {
                        z.b = 0x1f;
                    } else {
                        z.b = b;
                    }
                    break;
                case 0x27:
                case 0x28:
                    break;
                default:
                    z.r = 0x1f;
                    z.g = 0x1f;
                    z.b = 0x1f;
                    break;
            }
        }
    }
    self->col = z;
}
