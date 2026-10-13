/* func_020ab238 @ 0x020ab238, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020ab51c(unsigned int);
extern unsigned int func_020515b8(unsigned int);

struct UnkStruct_020ab238 {
    unsigned char pad_00[8];
    unsigned int arr[5];
    unsigned int max;
    unsigned int count;
};

void func_020ab238(struct UnkStruct_020ab238 *self)
{
    unsigned int n;
    unsigned int max;
    unsigned int i;
    unsigned int v;

    n = func_020ab51c(self->count);
    max = 0;
    for (i = 0; i < n; i++) {
        if (self->arr[i] != 0) {
            v = func_020515b8(self->arr[i]);
            if (v > max) {
                max = v;
            }
        }
    }
    self->max = max;
}
