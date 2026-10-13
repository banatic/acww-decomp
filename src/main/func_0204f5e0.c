/* func_0204f5e0 @ 0x0204f5e0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Grid {
    void *data;
    unsigned int width;
    unsigned int height;
};

extern void *func_02037e0c(void *p, int a, int b, unsigned char c);

void *func_0204f5e0(struct Grid *grid, unsigned int x, unsigned int y, int p3, int p4, unsigned char p5)
{
    void *ptr;

    if (x < grid->width && y < grid->height && grid->data != 0) {
        ptr = (void *) ((char *) grid->data + (x + y * grid->width) * 0x28);
    } else {
        ptr = 0;
    }

    if (ptr) {
        return func_02037e0c(ptr, p3, p4, p5);
    }
    return ptr;
}
