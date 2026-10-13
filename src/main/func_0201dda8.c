/* func_0201dda8 @ 0x0201dda8, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0201dda8 {
    char pad_00[0x100];
    void *unk_100;
    char arr104[0x1E];
    unsigned char unk_122;
    char pad_123[0x71];
    unsigned char bits;
    char pad_195[3];
    int counter;
} UnkStruct_0201dda8;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0201dda8_2;

typedef struct {
    u32 unk_00;
    unsigned char unk_04;
} Global;

extern Global data_020c8d18;
extern int data_021e5a2c[1];

extern int func_020036e8(void);
extern int func_0208150c(int);
extern void func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern int func_0207cec0(int *arr, int idx);
extern void func_02015e10(UnkStruct_0201dda8 *self, int x, int y);

void func_0201dda8(UnkStruct_0201dda8 *self, UnkStruct_0201dda8_2 *out)
{
    int i;
    int result1, result2;

    func_0208150c(*(int *) ((char *) self->unk_100 + 0x830));
    result1 = func_020036e8();
    result2 = data_020c8d18.unk_00;

    func_0202da38(self, &self->arr104, &self->unk_122, 0x1e, result1, result2, 1, 6, data_020c8d18.unk_04);

    out->ptr = &self->arr104;
    out->byte = self->unk_122;

    i = 0;
    while (i < 8) {
        if ((self->bits >> i) & 1) {
            int r;
            r = func_0208150c(func_0207cec0(data_021e5a2c, i));
            func_02015e10(self, r, 0);
            self->bits &= ~(1 << i);
            self->counter--;
            break;
        }
        i++;
    }
}
