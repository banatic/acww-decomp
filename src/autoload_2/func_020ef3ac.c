/* func_020ef3ac @ 0x020ef3ac, 0xec bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct_020ef3ac {
    int pad_00[3];
};

typedef struct {
    unsigned char pad_00[8];
    struct UnkStruct_020ef3ac arr[3];
    unsigned char pad_2C[8];
    unsigned short flags;
    unsigned char count;
} UnkStruct_020ef3ac_2;

extern int func_020ef968(struct UnkStruct_020ef3ac *p, int a, int b);
extern void func_020ef1f8(UnkStruct_020ef3ac_2 *s, int idx, int zero);
extern int func_020ef7fc(UnkStruct_020ef3ac_2 *s);
extern void func_020ef9dc(struct UnkStruct_020ef3ac *p, int a, int b, int c, short d);

int func_020ef3ac(UnkStruct_020ef3ac_2 *self, int arg1, int arg2, int arg3, short arg5)
{
    int found = 0xff;
    int i;

    if ((self->flags & 1) == 0) {
        return -1;
    }

    for (i = 0; i < self->count; i++) {
        if (func_020ef968(&self->arr[i], arg1, arg2) != 0) {
            found = i;
            func_020ef1f8(self, i, 0);
            break;
        }
    }

    if (found == 0xff) {
        found = func_020ef7fc(self);
    }

    if (found == self->count) {
        return -1;
    }

    func_020ef9dc(&self->arr[found], arg1, arg2, arg3, arg5);
    return found;
}
