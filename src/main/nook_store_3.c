/* nook_store_3: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020afa48 @ 0x020afa48, 0x8c bytes, Thumb
 * func_020afa14 @ 0x020afa14, 0x34 bytes, Thumb
 * func_020af9f0 @ 0x020af9f0, 0x22 bytes, Thumb
 * func_020af974 @ 0x020af974, 0x7c bytes, Thumb
 * func_020af950 @ 0x020af950, 0x22 bytes, Thumb
 * func_020af930 @ 0x020af930, 0x20 bytes, Thumb
 * func_020af90c @ 0x020af90c, 0x22 bytes, Thumb
 * func_020af8e0 @ 0x020af8e0, 0x2c bytes, Thumb
 * func_020af898 @ 0x020af898, 0x48 bytes, Thumb
 * func_020af890 @ 0x020af890, 0x8 bytes, Thumb
 * func_020af880 @ 0x020af880, 0x10 bytes, Thumb
 * func_020af870 @ 0x020af870, 0x10 bytes, Thumb
 * func_020af854 @ 0x020af854, 0x1c bytes, Thumb
 * func_020af83c @ 0x020af83c, 0x18 bytes, Thumb
 * func_020af788 @ 0x020af788, 0xb4 bytes, Thumb
 */

struct UnkStruct_020afa48 {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
};

struct Stack {
    volatile struct UnkStruct_020afa48 t;
    unsigned char rest[8];
};

typedef struct Pair {
    int x;
    int y;
} Pair;

struct UnkStruct_020af974 {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
};

struct UnkStruct_020af788 {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
};

extern void *func_020afad4(void *p);
extern void func_0209e140(void *p, int n);
extern int func_020afc84(Pair *p);
extern unsigned int func_0209e3ac(Pair *p, void *q, int n);
extern void func_0209e474(void *);
extern void func_0209e29c(void *param1, int param2);
extern unsigned int func_020af028(void *);
extern int func_020af648(void *object);
extern int data_021f395c;
extern void func_020afbcc(void *);
extern void func_020b00c8(void *dst, const void *src, int size);
extern int func_020b00a8(int a, int b, int c);
extern void *func_020b0038(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int func_020aff84(void *arg0, void *arg1, void *arg2, int arg3);
extern int func_020afb48(void *p, void *buf);
extern int func_020afcf4(int a, int b);
extern int func_02073d90(unsigned int x);
extern unsigned int data_020ccf94;
extern void MI_CpuCopy8(void *dest, const void *src, unsigned int n);

struct UnkStruct_020afa48 func_020afa48(void *a)
{
    struct Stack s;

    s.t.unk_03 = 0;
    s.t.unk_00 = s.t.unk_03;
    s.t.unk_01 = s.t.unk_00;
    s.t.unk_02 = s.t.unk_01;
    if (((struct UnkStruct_020afa48 *) func_020afad4(a))->unk_03 != 0) {
        *(unsigned int *) &s.rest[0] = 0;
        *(unsigned int *) &s.rest[4] = 0;
        s.rest[5] = ((struct UnkStruct_020afa48 *) func_020afad4(a))->unk_02;
        s.rest[4] = ((struct UnkStruct_020afa48 *) func_020afad4(a))->unk_01;
        s.rest[3] = ((struct UnkStruct_020afa48 *) func_020afad4(a))->unk_00;
        s.rest[2] = 6;
        s.rest[1] = 0;
        s.rest[0] = 0;
        *(unsigned short *) &s.rest[6] = 0;
        func_0209e140(&s.rest[0], 1);
        s.t.unk_02 = s.rest[5];
        s.t.unk_01 = s.rest[4];
        s.t.unk_00 = s.rest[3];
    }
    return s.t;
}

int func_020afa14(void *p0, void *p1)
{
    Pair local;
    local.x = 0;
    local.y = 0;
    if (func_020afc84(&local) && func_0209e3ac(&local, p1, 0x3c) + 1 <= 1) {
        return 1;
    }
    return 0;
}

int func_020af9f0(void *param)
{
    int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    return func_020afa14(param, local);
}

int func_020af974(int a, unsigned char *b)
{
    unsigned char local[8];
    if (((struct UnkStruct_020af974 *) func_020afad4((void *) a))->unk_03 == 0) {
        goto ret0_late;
    }
    *(unsigned int *) &local[0] = 0;
    *(unsigned int *) &local[4] = 0;
    local[5] = ((struct UnkStruct_020af974 *) func_020afad4((void *) a))->unk_02;
    local[4] = ((struct UnkStruct_020af974 *) func_020afad4((void *) a))->unk_01;
    local[3] = ((struct UnkStruct_020af974 *) func_020afad4((void *) a))->unk_00;
    local[2] = 6;
    local[1] = 0;
    local[0] = 0;
    *(unsigned short *) &local[6] = 0;
    func_0209e140(local, 1);
    if (local[5] == b[5] && local[4] == b[4] && local[3] == b[3]) {
        return 1;
    }
    return 0;
ret0_late:
    return 0;
}

int func_020af950(void *param)
{
    int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    return func_020af974((int) param, (unsigned char *) local);
}

int func_020af930(void *param1, void *param2)
{
    func_0209e29c(param2, 1);
    return func_020af974((int) param1, (unsigned char *) param2);
}

int func_020af90c(void *param)
{
    int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    return func_020af930(param, local);
}

void *func_020af8e0(int unused, int index)
{
    switch (index) {
        case 0:
            return (void *) 0x000061a8;
        case 1:
            return (void *) 0x00015f90;
        case 2:
            return (void *) 0x0003a980;
        default:
            return (void *) 0x0003a980;
    }
}

int func_020af898(void *param)
{
    unsigned int x = func_020af028(param);
    if (x == 3) {
        return x;
    }
    {
        unsigned int y = (unsigned int) func_020af8e0((int) param, x);
        if (*(unsigned int *) param < y) {
            goto label;
        }
        {
            int z;

            z = func_020af648(&data_021f395c);
            if (x == 2) {
                if (z == 0) {
                    goto label;
                }
                return x + 1;
            } else {
                return x + 1;
            }
        }
    }
label:
    return func_020af028(param);
}

void func_020af890(void *argument0)
{
    func_020afbcc((void *) argument0);
}

void func_020af880(void *arg0)
{
    void *dst = (char *) arg0 + 4;
    const void *src = (char *) arg0 + 0x5c;
    func_020b00c8(dst, src, 0x25);
}

int func_020af870(int a, int b)
{
    return func_020b00a8(b, 0x25, a + 0x5c);
}

void *func_020af854(unsigned int a, unsigned int b, unsigned int c)
{
    return func_020b0038(b, a + 4, a + 0x5c, 0x25, c);
}

int func_020af83c(char *arg0, void *arg1)
{
    return func_020aff84(arg1, arg0 + 4, arg0 + 0x5c, 0x25);
}

void func_020af788(void *p)
{
    unsigned char local0[8];
    unsigned char buffer[8];
    unsigned char tmp;
    int r4;

    r4 = func_020af898(p);
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }

    if ((int) func_020af028(p) >= r4) {
        return;
    }

    if (((struct UnkStruct_020af788 *) func_020afad4(p))->unk_03 != 0) {
        return;
    }

    *(unsigned int *) &local0[0] = 0;
    *(unsigned int *) &local0[4] = 0;

    func_0209e474(local0);
    func_0209e29c(local0, 2);
    MI_CpuCopy8(local0, buffer, 8);
    func_0209e140(buffer, 1);
    if (func_020afb48(p, buffer) != 0) {
        func_0209e29c(local0, 1);
    }

    ((struct UnkStruct_020af788 *) func_020afad4(p))->unk_03 = 1;
    tmp = local0[5];
    ((struct UnkStruct_020af788 *) func_020afad4(p))->unk_02 = tmp;
    tmp = local0[4];
    ((struct UnkStruct_020af788 *) func_020afad4(p))->unk_01 = tmp;
    tmp = local0[3];
    ((struct UnkStruct_020af788 *) func_020afad4(p))->unk_00 = tmp;

    func_0209e140(local0, 1);
    func_020afcf4(local0[4], local0[3]);
}
