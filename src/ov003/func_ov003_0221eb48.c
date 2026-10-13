/* func_ov003_0221eb48 @ 0x0221eb48, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_020af974(void *, void *);
extern int data_021f395c;

typedef struct {
    char pad_00[0x2b4];
    int unk_2B4;
} UnkStruct_0221eb48;

int func_ov003_0221eb48(UnkStruct_0221eb48 *p)
{
    struct {
        int w0;
        int w1;
    } s;
    if (p->unk_2B4 != -1) {
        s.w0 = 0;
        s.w1 = 0;
        func_0209e474(&s);
        if (func_020af974(&data_021f395c, &s) != 0) {
            return 1;
        }
    }
    return 0;
}
