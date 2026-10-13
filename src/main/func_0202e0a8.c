/* func_0202e0a8 @ 0x0202e0a8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9e58(void *);
extern void func_02082eec(void *);

typedef struct {
    char pad_00[0x28];
    unsigned short unk_28;
    char pad_2A[2];
    char unk_2C[4];
} func_0202e0a8_struct;

void *func_0202e0a8(func_0202e0a8_struct *self)
{
    func_020b9e58(self);
    self->unk_28 = 0xfff1;
    func_02082eec((void *) self->unk_2C);
    return self;
}
