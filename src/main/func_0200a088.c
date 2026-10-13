/* func_0200a088 @ 0x0200a088, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);
extern void func_02054860(void *);
extern void func_0200f95c(void *);

typedef struct {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x198];
    char unk_234[0xa0];
    int unk_2D4;
    char pad_2D8[0x8];
    int unk_2E0;
} UnkStruct_0200a088;

void func_0200a088(UnkStruct_0200a088 *self)
{
    int temp;

    temp = FX_MulFunc(self->unk_98, 0x3ae1);
    if (temp <= self->unk_2D4) {
        self->unk_2E0 = temp;
    }
    func_02054860(self->unk_234);
    func_0200f95c(self);
}
