/* func_ov096_0229d570 @ 0x0229d570, 0x64 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    char pad_00[0x294c];
    char data;
} Pad;

extern void func_ov002_02208d30(void *ptr, int val);
extern int func_ov002_02208d4c(void *ptr, int a, int b);
extern void func_ov096_0229ddd8(void *ptr);
extern void func_ov096_0229d1d4(void *ptr, int val);

void func_ov096_0229d570(void *param)
{
    func_ov002_02208d30(&((Pad *) param)->data, 0x22);
    func_ov002_02208d4c(&((Pad *) param)->data, 0xdd, 0x1d);
    func_ov002_02208d4c(&((Pad *) param)->data, 0xde, 0x1e);
    func_ov002_02208d4c(&((Pad *) param)->data, 0xdf, 0x1f);
    func_ov002_02208d4c(&((Pad *) param)->data, 0xe0, 0x20);
    func_ov002_02208d4c(&((Pad *) param)->data, 2, 0x22);
    func_ov096_0229ddd8(param);
    func_ov096_0229d1d4(param, 0);
}
