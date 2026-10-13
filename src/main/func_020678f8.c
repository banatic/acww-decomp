/* func_020678f8 @ 0x020678f8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020678f8;
struct VT {
    unsigned char pad_00[0x68];
    void *(*unk_68)(struct UnkStruct_020678f8 *o);
};
struct UnkStruct_020678f8 {
    struct VT *vt;
};
extern void func_020a8c1c(unsigned char *p);
extern void func_0207ee78(void *r, unsigned char *p);
int func_020678f8(unsigned char *p)
{
    int ok = 1;
    if (p[0x1e74] == 0) {
        struct UnkStruct_020678f8 *o = *(struct UnkStruct_020678f8 **) (p + 0x14a8);
        void *r = o->vt->unk_68(o);
        func_020a8c1c(p + 0x1d0c);
        if (r != 0) {
            func_0207ee78(r, p + 0x1d0c);
        } else {
            ok = 0;
        }
        p[0x1e74] = 1;
    }
    return ok;
}
