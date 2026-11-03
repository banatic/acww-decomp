/* music_volume_2: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02036574 @ 0x02036574, 0x10 bytes, Thumb
 * func_02036570 @ 0x02036570, 0x2 bytes, Thumb
 * func_02036560 @ 0x02036560, 0xe bytes, Thumb
 * func_02036558 @ 0x02036558, 0x8 bytes, Thumb
 * func_0203652c @ 0x0203652c, 0x2c bytes, Thumb
 * func_02036510 @ 0x02036510, 0x1c bytes, Thumb
 * func_020364ec @ 0x020364ec, 0x22 bytes, Thumb
 * func_020364e8 @ 0x020364e8, 0x2 bytes, Thumb
 * func_020364c0 @ 0x020364c0, 0x26 bytes, Thumb
 * func_02036490 @ 0x02036490, 0x2e bytes, Thumb
 * func_02036488 @ 0x02036488, 0x6 bytes, Thumb
 * func_02036480 @ 0x02036480, 0x6 bytes, Thumb
 * func_02036470 @ 0x02036470, 0x10 bytes, Thumb
 * func_02036468 @ 0x02036468, 0x6 bytes, Thumb
 * func_02036460 @ 0x02036460, 0x6 bytes, Thumb
 * func_02036458 @ 0x02036458, 0x6 bytes, Thumb
 * func_02036450 @ 0x02036450, 0x6 bytes, Thumb
 * func_02036448 @ 0x02036448, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned int word0;
    unsigned int word1;
    unsigned int word2;
} UnkStruct_02036560;

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[3];
    int unk_04;
    int unk_08;
} UnkStruct_02036558;

typedef struct {
    unsigned char pad_00[48];
    unsigned long unk_30;
} UnkStruct_02036488;

typedef struct {
    unsigned char pad_00[48];
    unsigned long unk_30;
} UnkStruct_02036480;

struct UnkStruct_02036470 {
    char pad_00[0x20];
    unsigned int unk_20;
};

typedef struct {
    unsigned char pad_00[32];
    unsigned long unk_20;
} UnkStruct_02036468;

typedef struct {
    unsigned char pad_00[64];
    unsigned long unk_40;
} UnkStruct_02036460;

typedef struct {
    unsigned char pad_00[64];
    unsigned long unk_40;
} UnkStruct_02036458;

typedef struct {
    unsigned char pad_00[80];
    unsigned long unk_50;
} UnkStruct_02036450;

typedef struct {
    unsigned char pad_00[80];
    unsigned long unk_50;
} UnkStruct_02036448;

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_0203637c(void *);
extern void func_020360a8(void *);
extern void func_02036034(void *);
extern void func_02036020(void *);
extern void func_0203600c(void *);
extern void func_020041cc(void);
extern unsigned int data_020c9f1c[];

void func_02036560(UnkStruct_02036560 *s);

int func_02036574(int arg)
{
    func_02036560((UnkStruct_02036560 *) arg);
    return arg;
}

void func_02036570(void *object) {}

void func_02036560(UnkStruct_02036560 *s)
{
    s->unk_00 = 0;
    s->unk_01 = 0;
    s->word0 = 0;
    s->word1 = 0;
    s->word2 = 0;
}

void func_02036558(UnkStruct_02036558 *p, int a, int b, int c)
{
    p->unk_04 = a;
    p->unk_08 = b;
    p->unk_00 = (unsigned char) c;
}

int *func_0203652c(int *s, int value)
{
    s[0] = value;
    __cxa_vec_ctor((void *) (s + 1), 8, 16, (((void (*)(void *)) (int (*)(void *)) func_02036574)), (void (*)(void *)) func_02036570);
    return s;
}

void *func_02036510(void *ptr)
{
    __cxa_vec_cleanup((void *) ((void *) ((unsigned char *) ptr + 4)), 8, 16, (void (*)(void *)) func_02036570);
    return ptr;
}

void func_020364ec(void *param)
{
    int i;
    void *p;
    unsigned int *ptr;

    p = param;
    for (i = 0; i < 8; i++) {
        func_02036560((UnkStruct_02036560 *) ((char *) p + 4 + (i << 4)));
    }
    ptr = (unsigned int *) ((char *) p + 0x84);
    *ptr = 0;
}

void func_020364e8(void *receiver) {}

void func_020364c0(void *arg)
{
    func_0203637c(arg);
    func_020360a8(arg);
    func_02036034(arg);
    func_02036020(arg);
    func_0203600c(arg);
}

void func_02036490(void *arg0)
{
    void *r5;
    int r4;
    void *r6;
    int r0;

    r5 = arg0;
    r0 = *(int *) ((char *) r5 + 0x30);
    r0 -= 8;
    if ((unsigned int) r0 <= 1) {
        func_020041cc();
    }
    r4 = 0;
    r6 = (char *) r5 + 4;
    do {
        func_02036560((UnkStruct_02036560 *) ((char *) r6 + (r4 << 4)));
        r4++;
    } while (r4 < 8);
    r0 = 0;
    *(int *) ((char *) r5 + 0x84) = r0;
}

void func_02036488(UnkStruct_02036488 *p)
{
    p->unk_30 = 7;
}

void func_02036480(UnkStruct_02036480 *p)
{
    p->unk_30 = 9;
}

void func_02036470(struct UnkStruct_02036470 *obj, int index)
{
    obj->unk_20 = data_020c9f1c[index];
}

void func_02036468(UnkStruct_02036468 *p)
{
    p->unk_20 = 6;
}

void func_02036460(UnkStruct_02036460 *p)
{
    p->unk_40 = 10;
}

void func_02036458(UnkStruct_02036458 *p)
{
    p->unk_40 = 12;
}

void func_02036450(UnkStruct_02036450 *p)
{
    p->unk_50 = 13;
}

void func_02036448(UnkStruct_02036448 *p)
{
    p->unk_50 = 15;
}
