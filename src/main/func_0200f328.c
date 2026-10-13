/* func_0200f328 @ 0x0200f328, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct DamageFlags {
    char pad_00[0xb0];
    unsigned int flags;
    char pad_B4[0x788];
    char data1[0x44];
    char data2[0x44];
};

extern int func_0200f290(struct DamageFlags *self, int value);
extern void func_020044c0(char *dest, void *src, unsigned int size, int param);

void func_0200f328(struct DamageFlags *self, void *param)
{
    int flag4 = (self->flags & 4) ? 1 : 0;
    if (flag4 != 0) {
        int flag2 = (self->flags & 2) ? 1 : 0;
        if (flag2 != 0) {
            return;
        }
    }
    if (func_0200f290(self, 0x19) != 0) {
        func_020044c0(self->data1, param, 0x7f, 0);
    } else {
        func_020044c0(self->data2, param, 0x7f, 0);
    }
}
