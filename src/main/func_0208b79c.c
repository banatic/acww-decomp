/* func_0208b79c @ 0x0208b79c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */
extern int func_0208b720(void *s);
extern void func_0208b77c(void *s);
extern void func_02051624(int);
extern void func_02051694(int);
extern int func_020e88dc(int *p, int a, int b);
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
    int call;
    int diff;
    int q;
    if (s->unk_82 == 0) {
        call = func_0208b720(s);
        if (s->unk_7C != call) {
            diff = call - s->unk_7C;
            if (diff < 0) {
                diff = -diff;
            }
            q = ((diff / 6) + 50) / 10;
            func_020e88dc(&s->unk_7C, call, q * 10 + 7);
            func_0208b77c(s);
            if (s->unk_38 != 0) {
                func_02051624(s->unk_38);
                func_02051694(s->unk_38);
            }
            ret = 1;
        }
    }
    return ret;
}
