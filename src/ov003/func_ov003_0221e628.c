/* func_ov003_0221e628 @ 0x0221e628, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int data[12];
} Buffer;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x64 - 0x60];
    int unk_64;
    char pad_68[0xc4 - 0x68];
    struct {
        int a, b, c;
    } sub_c4;
    unsigned short unk_D0;
} UnkStruct_0221e628;

extern Buffer data_021fbe48;
extern int func_0203f8d0(void *, void *);
extern void func_ov009_022648a4(UnkStruct_0221e628 *, Buffer *);
extern void func_020e9868(void *, int, int, int);

int func_ov003_0221e628(UnkStruct_0221e628 *self, Buffer *buf)
{
    struct {
        int a, b, c;
    } tmp;
    int cval;

    cval = self->unk_64 - 0x1000;
    tmp.a = self->unk_5C + 0x2000;
    tmp.b = 0;
    tmp.c = cval;

    self->unk_D0 = (unsigned short) func_0203f8d0(&self->sub_c4, &tmp);

    func_ov009_022648a4(self, buf);

    {
        Buffer *src = buf;
        data_021fbe48 = *src;
        func_020e9868(&data_021fbe48, -8192, 0, 4096);
        *buf = data_021fbe48;
    }

    return 1;
}
