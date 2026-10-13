/* func_020a86a4 @ 0x020a86a4, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020a87c8(void *arg, int idx);

struct UnkStruct_020a86a4 {
    unsigned char pad_00[12];
    void *x;
};

void func_020a86a4(struct UnkStruct_020a86a4 *a, unsigned char *b, unsigned char *c, unsigned char *d, unsigned char *e)
{
    *b = func_020a87c8(a->x, 0);
    *c = func_020a87c8(a->x, 1);
    *d = func_020a87c8(a->x, 2);
    *e = func_020a87c8(a->x, 3);
}
