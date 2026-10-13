/* func_ov126_0229fc98 @ 0x0229fc98, 0x40 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern int func_020996b8(void);
extern int func_0206fc8c(void);
extern void func_02072bb0(int a, int b);
extern int func_02072d4c(void);
extern void func_02072e90(int a, void *ptr);
extern void func_02051c08(void *dst, const void *src, int len);

typedef struct {
    char pad_00[0x4248];
    char data[10];
} UnkStruct_0229fc98;

void func_ov126_0229fc98(UnkStruct_0229fc98 *param)
{
    char buf[20];
    int a, b, c;
    func_020984e8();
    a = func_020996b8();
    b = func_0206fc8c();
    func_02072bb0(a, b);
    c = func_02072d4c();
    func_02072e90(c, buf);
    func_02051c08(buf, param->data, 10);
}
