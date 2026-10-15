/* func_02015fb0 @ 0x02015fb0, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Arg0 {
    char pad_00[0x40];
    int unk_40;
};

typedef struct {
    char data[0x44];
} UnkStruct_02015fb0;

extern void *func_020b5630(void *p);
extern int func_020b45d0(void *p, int a, int b, int c, int d, int e);
extern void func_02068404(int a, int b, void *p);
extern void *func_020b5618(void *p);

void func_02015fb0(struct Arg0 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    UnkStruct_02015fb0 local;
    if (arg1 < 0) {
        return;
    }
    func_020b5630(&local);
    func_020b45d0(&local, arg1, arg3, arg4, arg5, 0);
    func_02068404(arg0->unk_40, arg2, &local);
    func_020b5618(&local);
}
