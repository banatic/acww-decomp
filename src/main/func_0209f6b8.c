/* func_0209f6b8 @ 0x0209f6b8, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209f6b8 {
    int unk_00;
    int unk_04;
};

extern struct UnkStruct_0209f6b8 *func_020682e0(int arg);
extern int func_02068320(struct UnkStruct_0209f6b8 *arg);
extern void func_0203e210(int arg);
extern void func_0209f820(int arg0, int arg1);

void func_0209f6b8(int arg0)
{
    struct UnkStruct_0209f6b8 *p = func_020682e0(0);
    if (p->unk_04 == 0) {
        func_0203e210(func_02068320(p));
        func_0209f820(arg0, 0);
    }
}
