/* func_ov126_0229fc98 @ 0x0229fc98, 0x40 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_020996b8(int object);
extern int func_0206fc8c(void);
extern int func_02072bb0(int a, int b);
extern int func_02072d4c(unsigned int argument0);
extern void func_02072e90(int a, void *ptr);
extern int func_02051c08(void *dst, const void *src, int len);

typedef struct {
    char pad_00[0x4248];
    char data[10];
} UnkStruct_0229fc98;

void func_ov126_0229fc98(UnkStruct_0229fc98 *param)
{
    char buf[20];
    int a, b, c;
    a = func_020996b8(func_020984e8());
    b = func_0206fc8c();

    c = func_02072d4c((unsigned int) func_02072bb0(a, b));
    func_02072e90(c, buf);
    func_02051c08(buf, param->data, 10);
}
