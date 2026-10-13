/* func_0208b79c @ 0x0208b79c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the redundant mask keeps the constant 10 in r2 after r0 and r1 are set; without it the multiply is scheduled before the argument moves (an inline wrapper does not change this) */

extern int func_0208b720(void *s);
extern void func_0208b77c(void *s);
extern void func_02051624(int);
extern void func_02051694(int);
extern void func_020e88dc(int *out, int call, int a, int b);
typedef struct UnkStruct_0208b79c {
    char pad_00[0x38];
    int unk_38;
    char pad_3C[0x40];
    int unk_7C;
    char pad_80[0x2];
    unsigned char unk_82;
} UnkStruct_0208b79c;
int func_0208b79c(UnkStruct_0208b79c *s)
{
    int ret = 0;
    UnkStruct_0208b79c *ptr;
    int call;
    int diff;
    int q;
    if (s->unk_82 != 0) {
        goto done;
    }
    call = func_0208b720(s);
    if (s->unk_7C == call) {
        goto done;
    }
    ptr = s;
    diff = call - s->unk_7C;
    if (diff < 0) {
        diff = -diff;
    }
    q = ((diff / 6) + 50) / 10;
    func_020e88dc(&s->unk_7C, call, (q * (10 & 0xFFFFFFFF)) + 7, q * 10);
    func_0208b77c(s);
    if (s->unk_38 != 0) {
        func_02051624(s->unk_38);
        func_02051694(ptr->unk_38);
    }
    q = (ret = 1);
done:
    return ret;
}
