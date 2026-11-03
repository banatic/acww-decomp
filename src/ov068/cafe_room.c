/* cafe_room: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02274f08 @ 0x02274f08, 0x10 bytes, Thumb
 * func_ov068_02274efc @ 0x02274efc, 0xc bytes, Thumb
 * func_ov068_02274eec @ 0x02274eec, 0x10 bytes, Thumb
 * func_ov068_02274ee0 @ 0x02274ee0, 0xc bytes, Thumb
 */

typedef struct {
    char pad_00[0x294];
    int flag;
} UnkStruct_02274f08;

struct UnkStruct_ov068_02274efc {
    char pad_00[0x294];
    int unk_294;
};

struct UnkStruct_02274eec {
    char pad_00[0x294];
    int unk_294;
};

int func_ov068_02274f08(UnkStruct_02274f08 *self)
{
    self->flag = 1;
    return 1;
}

void func_ov068_02274efc(struct UnkStruct_ov068_02274efc *p)
{
    p->unk_294 = 1;
}

int func_ov068_02274eec(struct UnkStruct_02274eec *self)
{
    self->unk_294 = 0x1f;
    return 1;
}

void func_ov068_02274ee0(int *r0)
{
    r0[0x294 / 4] = 0x1f;
}
