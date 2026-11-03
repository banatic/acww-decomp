/* camera_grid_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208c688 @ 0x0208c688, 0x28 bytes, Thumb
 * func_0208c668 @ 0x0208c668, 0x20 bytes, Thumb
 * func_0208c658 @ 0x0208c658, 0x10 bytes, Thumb
 */

struct UnkStruct_0208c658;

typedef int (*VtableFunc)(struct UnkStruct_0208c658 *);

struct Vtable {
    VtableFunc funcs[4];
};

struct UnkStruct_0208c658 {
    struct Vtable *vtable;
};

extern void func_0208c3b8(void *);
extern void *func_0208a144(void *ptr);

void func_0208c688(void *param)
{
    unsigned char *p1;
    unsigned int *p2;
    unsigned int *p3;
    unsigned int *p4;
    unsigned int *p5;

    p1 = (unsigned char *) ((char *) param + 0xd4);
    *p1 = 0;

    p2 = (unsigned int *) ((char *) param + 0xc4);
    *p2 = 0;

    p3 = (unsigned int *) ((char *) param + 0xc8);
    *p3 = 0;

    p4 = (unsigned int *) ((char *) param + 0xcc);
    *p4 = 0;

    p5 = (unsigned int *) ((char *) param + 0xd0);
    *p5 = 0;

    func_0208c3b8(param);
}

void func_0208c668(void *p)
{
    int i;
    char *base;
    int stride;

    i = 0;
    base = (char *) p;
    base += 0xc;
    stride = 20;

    do {
        func_0208a144(base + i * stride);
        i++;
    } while (i < 9);
}

int func_0208c658(struct UnkStruct_0208c658 *self)
{
    return self->vtable->funcs[3](self);
}
