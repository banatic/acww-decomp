/* player_pick_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02245d30 @ 0x02245d30, 0x30 bytes, Thumb
 * func_ov004_02245cf4 @ 0x02245cf4, 0x3c bytes, Thumb
 */

struct VA {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

struct VB {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    char pad_04[0x7c];
};

struct UnkStruct_02245d30 {
    char pad_00[0x50];
    VA a;
    char pad_54[0x48];
    VB arr[5];
};

struct UnkStruct_02245cf4;

typedef void (UnkStruct_02245cf4::*PMF)(void);

struct UnkStruct_02245cf4 {};

struct UnkStruct_02245cf4_2 {
    PMF fn;
    int a, b;
};

extern "C" {
extern UnkStruct_02245cf4_2 data_ov004_0225fe94[];
}

extern "C" int func_ov004_02245d30(UnkStruct_02245d30 *self)
{
    unsigned char i;
    self->a.v2();
    for (i = 0; i < 5; i++) {
        self->arr[i].v2();
    }
    return 1;
}

extern "C" void func_ov004_02245cf4(UnkStruct_02245cf4 *self, int i)
{
    if (data_ov004_0225fe94[i].fn != 0) {
        (self->*(data_ov004_0225fe94[i].fn))();
    }
    *(int *) ((char *) self + 0x320) = i;
}
