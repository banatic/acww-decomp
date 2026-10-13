/* func_0204f564 @ 0x0204f564, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02037e44(void *ptr, int a, int b, int c, unsigned char d);

struct UnkStruct_0204f564 {
    char *base;
    unsigned int width;
    unsigned int height;
};

int func_0204f564(struct UnkStruct_0204f564 *self, int a, unsigned x, unsigned y, int b, int c, unsigned char d)
{
    unsigned w;
    char *ptr;
    int ret;

    w = self->width;
    if (x < w && y < self->height && self->base != 0) {
        ptr = self->base + (x + y * w) * 0x28;
    } else {
        ptr = 0;
    }
    ret = 0;
    if (ptr) {
        ret = func_02037e44(ptr, a, b, c, d);
    }
    return ret;
}
