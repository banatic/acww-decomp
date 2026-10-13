/* func_020b2a90 @ 0x020b2a90, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204e414(void);
extern int func_02037da8(void *a, void *b, void *c, void *d, void *e, int f);
extern int func_0204e3bc(void *a, int b, int c, int d, int e, void *f);
extern void func_02085f48(void);
extern void __register_global_object(void *a, void (*b)(void), void *c);
extern void func_020051b0(void);
extern unsigned short data_021f4b20;
extern unsigned short data_021f4b24;
extern unsigned int data_021f4b38;
extern unsigned int data_021f4b4c;
extern unsigned char data_021f4b88;
extern unsigned char data_021f4b94;
typedef struct {
    unsigned char *base;
    unsigned int width;
    unsigned int height;
} UnkStruct_020b2a90;
int func_020b2a90(void)
{
    UnkStruct_020b2a90 *self = (UnkStruct_020b2a90 *) func_0204e414();
    int r5;
    int a;
    int r4;
    int b;
    int c;
    int d;
    int e;
    unsigned char *ptr;
    if (self == 0) {
        return 0;
    }
    if ((data_021f4b38 & 1) == 0) {
        data_021f4b20 = 0x5020;
        __register_global_object(&data_021f4b20, func_020051b0, &data_021f4b88);
        data_021f4b38 |= 1;
    }
    a = 1;
    b = 1;
    c = 1;
    for (r5 = 1; r5 <= 4; r5++) {
        for (r4 = a; r4 <= 4; r4++) {
            if (((r4 < self->width) && (r5 < self->height)) && (self->base != 0)) {
                ptr = self->base + ((r4 + (r5 * self->width)) * 0x28);
            } else {
                ptr = 0;
            }
            if (ptr != 0) {
                if (func_02037da8(ptr, &d, &e, &data_021f4b20, &data_021f4b20, 0) != 0) {
                    if ((data_021f4b4c & b) == 0) {
                        data_021f4b24 = 0x500a;
                        __register_global_object(&data_021f4b24, func_020051b0, &data_021f4b94);
                        data_021f4b4c |= c;
                    }
                    if (func_0204e3bc(self, r4, r5, d, e, &data_021f4b24) != 0) {
                        func_02085f48();
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}
