/* func_ov009_022643f4 @ 0x022643f4, 0x50 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6590(void);
extern void *func_020b7d24(int a, void *b);

struct UnkStruct_022643f4 {
    unsigned char pad_00[0x235];
    unsigned char flag;
    unsigned char pad_236[0x52];
    void *array;
    unsigned char pad_28C[4];
    unsigned char count;
};

void func_ov009_022643f4(struct UnkStruct_022643f4 *self)
{
    char *cur;
    if (self->flag & 1) {
        return;
    }
    if (self->array == 0) {
        return;
    }
    cur = (char *) self->array;
    while (cur < (char *) self->array + self->count * 0x44) {
        func_020b7d24(func_020b6590(), cur);
        cur += 0x44;
    }
}
