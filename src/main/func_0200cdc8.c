/* func_0200cdc8 @ 0x0200cdc8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02006530(void *obj, int a, int b);
extern int FX_MulFunc(void *table, int index);
extern void func_0201108c(void *obj, int value);
extern int FX_Div(int numer, int denom);

struct UnkStruct_0200cdc8 {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x668];
    int unk_704;
};

void func_0200cdc8(struct UnkStruct_0200cdc8 *obj)
{
    int diff;
    int q;
    int tmp;
    int val;
    if (obj->unk_704 != 2) {
        func_02006530(obj, 0x93, 1);
        return;
    }
    diff = obj->unk_98 - 0x53f;
    if (diff < 0) {
        func_02006530(obj, 0x93, 1);
    }
    q = FX_Div(diff, 0x1a3);
    tmp = FX_MulFunc((void *) 0x00c17000, q);
    val = (tmp << 4) >> 16;
    func_0201108c(obj, val);
}
