/* func_0208e214 @ 0x0208e214, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned char pad_10[0x64];
    int unk_74;
} UnkStruct_0208e214;

extern void func_0208e24c(int);
extern void func_0208e05c(UnkStruct_0208e214 *);
extern void func_0208e0dc(UnkStruct_0208e214 *);
extern void func_0208e200(UnkStruct_0208e214 *);

void func_0208e214(UnkStruct_0208e214 *s)
{
    if (s->unk_74 != 0) {
        if (s->unk_0C == 4) {
            func_0208e24c(s->unk_0C);
        }
        func_0208e05c(s);
        func_0208e0dc(s);
        func_0208e200(s);
    }
}
