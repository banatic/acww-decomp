/* func_ov126_022a0680 @ 0x022a0680, 0x34 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned char a8;
    unsigned char a9;
    unsigned char aa;
} UnkStruct_022a0680;

extern void func_ov126_0229f7a8(UnkStruct_022a0680 *s, int n);
extern void func_ov126_0229f7b8(UnkStruct_022a0680 *s, int n);

void func_ov126_022a0680(UnkStruct_022a0680 *s)
{
    s->aa = s->a8;
    if (s->aa != s->a9) {
        func_ov126_0229f7b8(s, 4);
    } else {
        func_ov126_0229f7a8(s, 4);
    }
}
