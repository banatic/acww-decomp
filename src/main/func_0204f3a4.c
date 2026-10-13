/* func_0204f3a4 @ 0x0204f3a4, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *data;
    unsigned int width;
    unsigned int height;
} SInfo;

extern int func_02037d48(void *ptr, int a, int b);

int func_0204f3a4(SInfo *s, unsigned int x, unsigned int y, int arg3, int arg4)
{
    void *ptr;
    int result;

    if (x < s->width && y < s->height && s->data != 0) {
        ptr = (char *) s->data + (x + y * s->width) * 0x28;
    } else {
        ptr = 0;
    }

    result = 0;
    if (ptr != 0) {
        result = func_02037d48(ptr, arg3, arg4);
    }

    return result;
}
