/* field_actor_states_6: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02008db8 @ 0x02008db8, 0x8 bytes, Thumb
 * func_02008da8 @ 0x02008da8, 0x10 bytes, Thumb
 * func_02008d5c @ 0x02008d5c, 0x4c bytes, Thumb
 * func_02008d2c @ 0x02008d2c, 0x30 bytes, Thumb
 * func_02008cec @ 0x02008cec, 0x40 bytes, Thumb
 * func_02008cac @ 0x02008cac, 0x40 bytes, Thumb
 */

struct UnkStruct_02008d5c {
    char pad_00[0xc];
    short unk_0C;
};

struct UnkStruct_02008d5c_2 {
    char pad_00[0x6e0];
    char unk_6E0[0xf4];
    short unk_7D4;
    char pad_7D6[0x11a];
    char unk_8F0[1];
};

struct UnkStruct_02008cac {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x51F];
    int unk_7F0;
    char pad_7F4[0x8];
    int unk_7FC;
};

extern void func_02077910(int, int);
extern int func_020778f8(int a);
extern void func_020109a0(void *, unsigned int, unsigned int, unsigned short);
extern int func_020912d4(int, void *, int, int);
extern int func_0200f328(void *, int);
extern int func_02008dc0(void *param1, int param2, int param3, void *param4);
extern int func_02011404(signed short *a, signed short b, unsigned int c, unsigned int d, unsigned int e);
extern void func_020110a0(unsigned char *a, signed short *b);
extern int func_02056f94(void *);
extern int func_02008258(struct UnkStruct_02008cac *, int);
extern int func_0200d4e8(struct UnkStruct_02008cac *, int, int, int);

void func_02008db8(int argument0, int argument1)
{
    func_02077910((int) argument0, (int) argument1);
}

void func_02008da8(int a, unsigned short *p)
{
    *p = func_020778f8(a);
}

void func_02008d5c(struct UnkStruct_02008d5c_2 *a, struct UnkStruct_02008d5c *b, int previous)
{
    short val = b->unk_0C;
    func_020109a0(a, 0x70, 3, 0);
    func_020912d4(0x43, a->unk_6E0, 0, 0);
    func_0200f328(a, 0x86);
    a->unk_7D4 = val;
    func_02008db8((int) a->unk_8F0, val);
}

void func_02008d2c(void *param1, void *param2)
{
    int sp_value;
    void *temp;

    func_02008da8((int) ((char *) param1 + 0x8f0), (unsigned short *) (&sp_value));
    temp = param1;
    func_02008dc0(temp, *(short *) &sp_value, 6, param2);
}

void func_02008cec(unsigned char *self)
{
    signed short s;

    s = *(signed short *) (self + 0x8e);
    func_02011404(&s, *(signed short *) (self + 0x7d4), 0x800, 0x1770000, 0xc0000);
    func_020110a0(self, &s);
}

void func_02008cac(struct UnkStruct_02008cac *obj)
{
    if (func_02056f94(&obj->unk_2D0) != 0) {
        obj->unk_7FC = func_02008258(obj, obj->unk_7F0);
        func_0200d4e8(obj, 3, 1, -1);
    }
}
