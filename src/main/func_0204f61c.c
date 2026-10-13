/* func_0204f61c @ 0x0204f61c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02037d80(void *ptr, unsigned int z);

struct UnkStruct_0204f61c {
    void *data;
    unsigned int width;
    unsigned int height;
};

void *func_0204f61c(struct UnkStruct_0204f61c *s, unsigned int x, unsigned int y, unsigned int z)
{
    void *result;
    void *ret;

    if (x < s->width && y < s->height && s->data != 0) {
        result = (void *) ((char *) s->data + (x + y * s->width) * 40);
    } else {
        result = 0;
    }

    ret = 0;
    if (result != 0) {
        ret = func_02037d80(result, z);
    }
    return ret;
}
