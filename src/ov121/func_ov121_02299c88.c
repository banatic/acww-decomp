/* func_ov121_02299c88 @ 0x02299c88, 0x44 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb5];
    unsigned char b5;
    unsigned char b6;
} UnkStruct_02299c88;

extern int func_ov121_02299a5c(UnkStruct_02299c88 *p, int arg1);
extern void func_ov121_0229af00(UnkStruct_02299c88 *p, unsigned char arg1, int arg2);
extern void func_ov121_02299a4c(UnkStruct_02299c88 *p, int arg1);

void func_ov121_02299c88(UnkStruct_02299c88 *p, unsigned char q)
{
    if (func_ov121_02299a5c(p, 0x200) != 0) {
        func_ov121_0229af00(p, p->b5, 2);
    }
    p->b5 = q;
    p->b6 = 15;
    func_ov121_02299a4c(p, 0x200);
}
