/* pockets_town_2: 4 functions, module ov098
 * mwccarm 1.2/base -O4,s
 * func_ov098_022a2bfc @ 0x022a2bfc, 0xdc bytes, Thumb
 * func_ov098_022a2b6c @ 0x022a2b6c, 0x90 bytes, Thumb
 * func_ov098_022a2b1c @ 0x022a2b1c, 0x50 bytes, Thumb
 * func_ov098_022a2ac8 @ 0x022a2ac8, 0x54 bytes, Thumb
 */

typedef struct {
    int x, y;
} Pt;

typedef struct {
    int data[2];
} UnkStruct_022a2b6c;

typedef struct {
    unsigned char pad_00[0xb6];
    unsigned char byte6;
    unsigned char pad_B7[0xc4 - 0xb6 - 1];
    int unk_C4;
    unsigned char pad_C8[0x2e20 - 0xc4 - 4];
    int unk_2E20;
    int unk_2E24;
} UnkStruct_022a2b6c_2;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} GlobalType;

struct UnkStruct_022a2b1c {
    char pad_00[0xC4];
    int unk_C4;
};

typedef struct GameObj {
    char pad_00[182];
    unsigned char byte_field;
    char pad_B7[11625];
    int int_field1;
    int int_field2;
} GameObj;

extern void *func_020984e8(void);
extern unsigned short *func_02099728(void *);
extern char *func_020961a8(int);
extern void *func_0204e414(void);
extern void func_0204f818(int *, int *, void *);
extern Pt *func_ov098_022a2cd8(void *, short);
extern unsigned short *func_0204f5e0(void *, int, int, int, int, int);
extern const short data_ov098_022a3240[];
extern void func_ov096_0229fb9c(void *p);
extern void func_ov096_0229f874(void *p, int a, int b, int c);
extern unsigned short func_ov096_0229f0dc(void *p, int val);
extern int func_02043db4(int a, int *arr, int count, int flag, unsigned short extra);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern GlobalType *data_020ccf94;
extern int func_020436a8(int);
extern void func_020431b8(int);
extern void func_0204f794(int *out, int a, int b);
extern int func_ov003_02219b90(int *a, short *b);
extern void func_ov096_0229f5ac(GameObj *self, unsigned char byte);

void func_ov098_022a2ac8(GameObj *self);

int func_ov098_022a2bfc(void *obj)
{
    void *h2;
    int zA;
    int zB;
    int a;
    int b;
    char *st;
    unsigned int hit;
    unsigned short id;
    int i;
    int sx, sy;
    int base;
    int qx, qy;
    unsigned short *ip;
    Pt *p;
    unsigned short *r;

    ip = func_02099728(func_020984e8());
    hit = 0;
    id = *ip;
    if (id >= 0x1369 && id <= 0x1369) {
        hit = 1;
    }
    if (hit == 0 && !(id >= 0x136a && id <= 0x136a)) {
        return 0;
    }

    st = func_020961a8(4);
    a = 0;
    b = 0;
    h2 = func_0204e414();
    func_0204f818(&a, &b, st + 0x5c);
    i = 0;
    base = *(short *) (st + 0x8e);
    zB = 0;
    zA = 0;
    for (; i < 3; i++) {
        p = func_ov098_022a2cd8(obj, (short) (base + data_ov098_022a3240[i]));
        sx = a + p->x;
        sy = b + p->y;
        qx = sx >> 4;
        qy = sy >> 4;
        r = func_0204f5e0(h2, qx, qy, sx - (qx << 4), sy - (qy << 4), zA);
        if (r != 0) {
            hit = zB;
            if (*r >= 0xfc && *r <= 0xfd) {
                hit = 1;
            }
            if (hit != 0) {
                *(int *) ((char *) obj + 0x2e20) = sx;
                *(int *) ((char *) obj + 0x2e24) = sy;
                return 1;
            }
        }
    }
    return 0;
}

void func_ov098_022a2b6c(UnkStruct_022a2b6c_2 *p)
{
    UnkStruct_022a2b6c local;
    unsigned short h;

    if (func_ov098_022a2bfc(p) == 0) {
        func_ov096_0229fb9c(p);
        func_ov096_0229f874(p, 13, 255, 1);
        return;
    }

    h = func_ov096_0229f0dc(p, p->byte6);
    local.data[0] = p->unk_2E20;
    local.data[1] = p->unk_2E24;
    p->unk_C4 = func_02043db4(data_020ccf94->unk_64, local.data, 2, 0, h);

    if (p->unk_C4 == -1) {
        func_ov096_0229fb9c(p);
        func_ov096_0229f874(p, 13, 255, 1);
    } else {
        func_ov002_02208098(p, 45);
    }
}

void func_ov098_022a2b1c(struct UnkStruct_022a2b1c *arg)
{
    int ret = func_020436a8(arg->unk_C4);
    switch (ret) {
        case 1:
            func_ov002_02208098((void *) arg, 0x2E);
            func_ov098_022a2ac8((GameObj *) arg);
            break;
        case 2:
            func_ov096_0229fb9c((void *) arg);
            func_ov096_0229f874((void *) arg, 3, 0xFF, 1);
            break;
        default:
            return;
    }
    func_020431b8(arg->unk_C4);
    arg->unk_C4 = -1;
}

void func_ov098_022a2ac8(GameObj *self)
{
    short local_0;
    int local_4[3];

    func_0204f794(local_4, self->int_field1, self->int_field2);
    local_0 = (short) func_ov096_0229f0dc((void *) self, (unsigned char) self->byte_field);
    if (func_ov003_02219b90(local_4, &local_0) != 0) {
        func_ov096_0229f5ac(self, self->byte_field);
        func_ov002_02208098((void *) self, 0x2f);
    }
}
