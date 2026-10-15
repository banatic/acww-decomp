/* func_0209c020 @ 0x0209c020, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209e3ac(void *a, void *b, int n);
extern int func_0209e380(void *a, void *b);
extern void *func_0209c4a8(void *p);
extern int func_0209c38c(unsigned int);
extern void func_0209c32c(void *a, void *b);
extern void func_0209c470(void *a, void *b);
extern void func_0209e474(void *);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);

struct UnkStruct_0209c020 {
    unsigned char pad_00[0x10];
    unsigned char unk_10;
    unsigned char unk_11[0x10];
    unsigned char b0 : 1;
};

int func_0209c020(struct UnkStruct_0209c020 *obj, void *b)
{
    if (obj->unk_10 == 0xa) {
        if (b == 0 || (func_0209e3ac(b, obj, 0x3f) == 1 && func_0209e380(obj, b) >= 1)) {
            b = func_0209c4a8(obj->unk_11);
            if (func_0209c38c((unsigned int) b) != 0) {
                func_0209c32c(obj, b);
                func_0209c470(obj->unk_11, b);
                obj->b0 = 0;
                func_0209e474(obj);
                MI_CpuCopy8(obj, (char *) obj + 8, 8);
                return (int) b;
            }
        }
    }
    return 0xc;
}
