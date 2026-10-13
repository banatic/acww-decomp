/* func_020a84e4 @ 0x020a84e4, 0x76 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a86a4(void *self, unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d);
extern void func_020a8a34(void *p, int base);
typedef struct {
    int x;
    int y;
} Ptr;
typedef struct {
    int pad_00;
    int pad_04;
    int a;
    int b;
} UnkStruct_020a84e4;
int func_020a84e4(UnkStruct_020a84e4 *self, unsigned char *d1, Ptr *p1, unsigned char *d2, Ptr *p2, unsigned char *d3, Ptr *p3,
                  unsigned char *d4, Ptr *p4)
{
    unsigned char tmp[8];
    int base;
    Ptr *ptrs[4];
    int total;
    int i;
    int inc;
    func_020a86a4(self, &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
    *d1 = tmp[0];
    *d2 = tmp[1];
    *d3 = tmp[2];
    *d4 = tmp[3];
    ptrs[0] = p1;
    ptrs[1] = p2;
    ptrs[2] = p3;
    ptrs[3] = p4;
    base = (self->b + self->a) + 2;
    total = 2;
    for (i = 0; i < 4; i++) {
        func_020a8a34(ptrs[i], base);
        inc = ptrs[i]->y + 2;
        total += inc;
        base += inc;
    }

    return total;
}
