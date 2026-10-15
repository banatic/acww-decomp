/* func_ov050_02262b08 @ 0x02262b08, 0x50 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_02099f1c(void *dst, int (*predicate)(unsigned short *));
extern int func_0209ad9c(int a, int b);
extern int func_0209b4d4(void *object);
extern void func_0209abc8(int a);
extern void func_0209bb90(int a, int b);
extern int func_ov050_022634b4(unsigned short *value);

struct UnkStruct_02262b08 {
    unsigned char pad_00[0xD0];
    int unk_D0;
};

void func_ov050_02262b08(struct UnkStruct_02262b08 *param0, int param1)
{
    unsigned char buf[4];
    int result;

    func_02099f1c(buf, func_ov050_022634b4);
    if (buf[2] >= 7) {
        param0->unk_D0 = 8;
    } else {
        param0->unk_D0 = 9;
    }
    result = func_0209b4d4((void *) (func_0209ad9c(param1, 0)));
    func_0209abc8(param1);
    func_0209bb90(result, 2);
}
