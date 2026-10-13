/* func_ov068_0226f444 @ 0x0226f444, 0x58 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f7e0(void *a, void *b);
extern void *func_020b03f8(int param);

struct UnkStruct_0226f444 {
    char pad_00[8];
    unsigned int flag;
    char pad_0C[0x50];
    char unk_5C;
    char pad_5D[0x31b];
    unsigned short u16field;
    char pad_37A[0xe];
    char unk_388;
};

struct Quad {
    int a;
    int b;
    int c;
    int d;
};

int func_ov068_0226f444(struct UnkStruct_0226f444 *self)
{
    int flag;
    void *p;
    struct Quad *arr;

    self->u16field &= ~0x10;
    self->u16field |= 0x20;
    func_0204f7e0(&self->unk_388, &self->unk_5C);
    flag = (self->flag & 1);
    p = func_020b03f8(1);
    flag &= 1;
    arr = (struct Quad *) p;
    arr[flag].a = 0;
    arr[flag].b = 0;
    arr[flag].c = 0;
    arr[flag].d = 0x800;
    return 1;
}
