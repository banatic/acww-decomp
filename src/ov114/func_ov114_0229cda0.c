/* func_ov114_0229cda0 @ 0x0229cda0, 0x2c bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

struct Elem {
    char data[0x6c];
};

struct UnkStruct_0229cda0 {
    char pad_00[0x106c];
    struct Elem arr[4];
    char pad_121C[0x9a];
    unsigned char flag;
};

extern void func_02070b84(struct Elem *);

void func_ov114_0229cda0(struct UnkStruct_0229cda0 *self)
{
    int i = 0;
    self->flag = 0;
    for (; i < 4; i++) {
        func_02070b84(&self->arr[i]);
    }
}
