/* func_ov003_0220e9d8 @ 0x0220e9d8, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x98];
    int val;
} UnkStruct_0220e9d8;

extern int func_020113a4(int a, int b, int c);
extern void func_0201107c(void *p, int *q);

void func_ov003_0220e9d8(UnkStruct_0220e9d8 *s)
{
    if (s->val != 0) {
        int temp = func_020113a4(s->val, 0, 0x171);
        func_0201107c(s, &temp);
    }
}
