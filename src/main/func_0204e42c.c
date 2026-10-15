/* func_0204e42c @ 0x0204e42c, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x28];
} Elem;

typedef struct {
    Elem *data;        // 0x00
    int width;         // 0x04
    int height;        // 0x08
    char pad_0C[0x10]; // 0x0c-0x1b
    int unk_1C;        // 0x1c
} UnkStruct_0204e42c;

extern int data_021c9ab0;
extern void func_020e9b9c(int);
extern int func_02030ddc(int, int, int, int);
extern int func_02037e84(Elem *);
extern int func_0203750c(void);
extern int func_020377d8(int, int);
extern void func_02037ecc(Elem *, int, int, int);

void func_0204e42c(UnkStruct_0204e42c *self)
{
    int gv;         // [sp, #0]
    int init;       // [sp, #4]
    Elem *fallback; // [sp, #8]
    int a;          // [sp, #0xc]
    int arg;        // [sp, #0x10]
    int i, j;
    Elem *ptr;
    int b;

    func_020e9b9c(data_021c9ab0);
    func_02030ddc(self->width, self->height, 0, self->unk_1C);

    init = 0;
    fallback = 0;
    arg = 0;

    for (i = 0; i < self->height; i++) {
        for (j = init; j < self->width; j++) {
            if ((unsigned int) j < (unsigned int) self->width && (unsigned int) i < (unsigned int) self->height &&
                self->data != 0) {
                ptr = &self->data[i * self->width + j];
            } else {
                ptr = fallback;
            }
            if (ptr != 0) {
                a = func_02037e84(ptr);
                gv = data_021c9ab0;
                func_0203750c();
                b = func_020377d8(a, gv);
                func_02037ecc(ptr, arg, b, self->unk_1C);
            }
        }
    }
}