/* func_ov003_0221c0dc @ 0x0221c0dc, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ae3b8(void *);
extern int func_020ae614(int, void *);
extern void func_020ae774(void *);
extern void func_020ae75c(void *);
extern void func_02068404(int, int, void *);
extern int data_021f3b30;

struct Struc {
    char pad_00[0x10a];
    unsigned char unk_10A;
    char pad_10B[0x21];
    int unk_12C;
};

void func_ov003_0221c0dc(struct Struc *p)
{
    char local[0x38];
    if (p->unk_10A != 2) {
        return;
    }
    func_020ae774(local);
    if (func_020ae614(func_020ae3b8(&data_021f3b30), local) != 0) {
        func_02068404(p->unk_12C, 0, local);
    }
    func_020ae75c(local);
}
