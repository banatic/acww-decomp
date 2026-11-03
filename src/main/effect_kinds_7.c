/* effect_kinds_7: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020934a4 @ 0x020934a4, 0x28 bytes, Thumb
 * func_02093448 @ 0x02093448, 0x5c bytes, Thumb
 * func_020933ec @ 0x020933ec, 0x5c bytes, Thumb
 * func_020933c0 @ 0x020933c0, 0x2a bytes, Thumb
 */

struct func_02093448_obj {
    unsigned char pad_00[0x34];
    int unk_34;
    unsigned char pad_38[0x8];
};

typedef struct {
    unsigned char pad_00[0x34];
    unsigned int unk_34;
    unsigned char pad_38[8];
} UnkStruct_020933ec;

typedef struct OtherStruct {
    char pad_00[0x20];
    short result;
} OtherStruct;

typedef struct UnkStruct_020933c0 {
    char pad_00[8];
    OtherStruct *ptr;
    char pad_0C[48];
    short short1;
    char pad_3E[2];
    short short2;
    char pad_42[54];
    int flag;
} UnkStruct_020933c0;

extern int func_02094b58(int, int, int, int, int, int);
extern unsigned char data_020e28c4[];
extern int func_02034270(void *, int, int, int);
extern void func_0203423c(void *);
extern int func_020b6598(void);
extern int func_02094cf8(int, int, int, int, int, void *);
extern unsigned char data_020e29dc[];
extern int func_020e8ed8(int a, int b);

void func_020934a4(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e28c4;
    func_02094b58(0x70, r0, r1, r2, sp[0], sp[1]);
}

int func_02093448(int a, int b, int c, int d)
{
    struct func_02093448_obj obj;
    int st;
    int kind;
    int result;

    st = func_02034270(&obj, b, 0, 0);
    kind = obj.unk_34;

    if (kind == 0x13 || (func_020b6598() != 0 && kind == 3)) {
        result = func_02094cf8(0x55, a, b, c, d, ((int *) data_020e29dc));
        func_0203423c(&obj);
        return result;
    } else {
        func_0203423c(&obj);
        return 3;
    }
}

int func_020933ec(int arg1, int arg2, int arg3, int arg4)
{
    UnkStruct_020933ec obj;
    int field;

    func_02034270(&obj, arg2, 0, 0);
    field = obj.unk_34;

    if (field == 0x13 || (func_020b6598() != 0 && field == 3)) {
        int r = func_02094cf8(0x56, arg1, arg2, arg3, arg4, (void *) data_020e29dc);
        func_0203423c(&obj);
        return r;
    } else {
        func_0203423c(&obj);
        return 3;
    }
}

void func_020933c0(UnkStruct_020933c0 *a, int b)
{
    if (b == 1) {
        OtherStruct *p = a->ptr;
        if (p != 0) {
            p->result = func_020e8ed8(a->short1, a->short2);
            a->flag = 0;
        }
    }
}
