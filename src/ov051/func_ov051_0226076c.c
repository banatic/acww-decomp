/* func_ov051_0226076c @ 0x0226076c, 0x30 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

struct func_ov051_0226076c_A;
extern unsigned char func_ov051_022605e8(struct func_ov051_0226076c_A *, int);
extern void func_0206844c(void *, void *, void *);
extern void func_0209c5a4(void *);
extern void *data_ov051_022615c0;

struct func_ov051_0226076c_A {
    char pad_00[0x40];
    void *unk_40;
};

void func_ov051_0226076c(struct func_ov051_0226076c_A *a, void *b)
{
    unsigned char byte;
    byte = func_ov051_022605e8(a, 0x17);
    func_0206844c(a->unk_40, &byte, data_ov051_022615c0);
    func_0209c5a4(b);
}
