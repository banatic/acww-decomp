/* func_02083148 @ 0x02083148, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[4];
    unsigned int unk_04;
} UnkStruct_02083148;
extern unsigned char *func_020831c0(unsigned int, int);
extern void func_02083274(unsigned char *x, int k, int c);

int func_02083148(UnkStruct_02083148 *p, unsigned int i, int c)
{
    int r = 0;
    if (i < p->unk_04) {
        unsigned int n4 = 4;
        n4 += i;
        func_02083274(func_020831c0(4, 0) + 8 + i * 0x6c, n4, c);
        r = 1;
    }
    return r;
}
