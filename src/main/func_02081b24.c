/* func_02081b24 @ 0x02081b24, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02081ff0(void *);
extern void func_02081b00(void *, void *);
extern void func_020a8a70(void *, void *, int, int);
extern void func_02081fd8(void *);

void func_02081b24(void *param0, void *param1)
{
    unsigned char stack[0x24];
    func_02081ff0(stack);
    func_02081b00(param0, stack);
    func_020a8a70(param1, stack, 0, 0);
    func_02081fd8(stack);
}
