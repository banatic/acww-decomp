/* func_ov004_0223f110 @ 0x0223f110, 0x108 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

// Preserve the ROM register reuse and instruction scheduling.
#pragma opt_propagation off
typedef struct {
    int x, y, z;
} Vec;
extern void func_02089bec(void *, Vec *, int, int, int, int, int, unsigned char, int);
extern void func_02089fc8(void *);
void func_ov004_0223f110(unsigned char *self)
{
    Vec positions[4];
    int width[4], height[4];
    unsigned char count, i;
    if (*(int *) (self + 8) == 1) {
        positions[0].x = 0x13000;
        positions[0].y = 0x800;
        positions[0].z = 0xe300;
        width[0] = 0x1000;
        height[0] = 0x1000;
        positions[1].x = 0x19400;
        positions[1].y = 0x800;
        positions[1].z = 0xf300;
        width[1] = 0x1000;
        height[1] = 0x1000;
        positions[2].x = 0x10800;
        positions[2].y = 0x600;
        positions[2].z = 0xc600;
        width[2] = 0xc00;
        height[2] = 0x600;
        positions[3].x = 0x10800;
        positions[3].y = 0x600;
        positions[3].z = 0x15700;
        width[3] = 0xc00;
        height[3] = 0x600;
        count = 4;
    } else {
        positions[0].x = 0x7900;
        positions[0].y = 0x800;
        positions[0].z = 0xe100;
        width[0] = 0x3c00;
        height[0] = 0x800;
        positions[1].x = 0xaa00;
        positions[1].y = 0x800;
        positions[1].z = 0xcd00;
        width[1] = 0x3c00;
        height[1] = 0x800;
        count = 2;
    }
    for (i = 0; i < count; ++i) {
        int offset = i * 4;
        void *part = self + 0x50 + i * 0x4c;
        func_02089bec(part, &positions[i], *(int *) ((char *) height + offset), *(int *) ((char *) width + offset), 0x42, 0x80,
                      0, 255, 0x1000);
        func_02089fc8(part);
    }
}
