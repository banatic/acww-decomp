/* func_0204f658 @ 0x0204f658, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02037d9c(void *);

typedef struct {
    void *data;          // offset 0
    unsigned int width;  // offset 4
    unsigned int height; // offset 8
} UnkStruct_0204f658;

void *func_0204f658(UnkStruct_0204f658 *a, unsigned int x, unsigned int y)
{
    void *ret = 0;
    void *p;
    if (x < a->width && y < a->height && a->data) {
        p = (char *) a->data + (x + y * a->width) * 40;
    } else {
        p = 0;
    }
    if (p) {
        ret = func_02037d9c(p);
    }
    return ret;
}
