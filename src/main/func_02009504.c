/* func_02009504 @ 0x02009504, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8e];
    signed short unk_8E;
    char pad_90[0x744];
    signed short unk_7D4;
} UnkStruct_02009504;

extern void func_0200c3b0(void *param, int a, int b, int c);
extern void func_0200f268(void *param, int a);

void func_02009504(UnkStruct_02009504 *param)
{
    if (param->unk_7D4 == param->unk_8E) {
        func_0200c3b0(param, 3, 5, -1);
        func_0200f268(param, 6);
    }
}
