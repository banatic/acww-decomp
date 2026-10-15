/* func_020bbe94 @ 0x020bbe94, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6840(int);
extern void func_02004290(void *p, int val);
extern char *func_02137550(void *ptr, int size);
extern void func_020042b0(void *p, void *local);
extern void func_020bbdc8(void *p);
extern int data_020d2334[];

struct UnkStruct_020bbe94 {
    long long unk_00;
    int unk_08;
};

void func_020bbe94(void *p)
{
    struct UnkStruct_020bbe94 local;

    if (*(int *) ((char *) p + 0xc) != 0) {
        int idx = func_020b6840(0);
        int v = data_020d2334[idx];
        if (v >= 0) {
            func_02004290(p, v);
        }
    }

    func_02137550(&local, 0xc);
    local.unk_08 = *(int *) ((char *) p + 0xc) >> 8;
    func_020042b0(p, &local);
    func_020bbdc8(p);
}
