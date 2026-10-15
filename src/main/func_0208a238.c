/* func_0208a238 @ 0x0208a238, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern u32 data_020d0a44[];
extern u32 data_020d0a34[];
extern u64 data_020d6fcc[];

extern void func_0208a1f0(void *obj, void *data);
extern void func_0208a1ec(void *obj, int flag);
extern void *func_0208a144(void *obj);

typedef struct {
    char pad_00[0xc];
    char sub0;
    char pad_0D[0x20 - 0xc - 1];
    char sub1;
    char pad_21[0x34 - 0x20 - 1];
    u32 unk_34;
    char pad_38[0x40 - 0x38];
    u8 unk_40;
} Parent;

void func_0208a238(Parent *self, int idx)
{
    u32 t = (u32) idx << 2;
    u32 word = *(u32 *) ((unsigned char *) data_020d0a44 + t);
    u32 next;
    u32 other;

    if (self->unk_40 != 0) {
        word += 6;
    }
    next = word + 1;
    other = *(u32 *) ((unsigned char *) data_020d0a34 + t);
    self->unk_34 = idx;

    func_0208a1f0(&self->sub0, &data_020d6fcc[word]);
    func_0208a1ec(&self->sub0, other);
    func_0208a144(&self->sub0);

    func_0208a1f0(&self->sub1, &data_020d6fcc[next]);
    func_0208a1ec(&self->sub1, other);
    func_0208a144(&self->sub1);
}
