/* chat_scene_6: 4 functions, module ov111
 * mwccarm 1.2/base -O4,s
 * func_ov111_022a0b9c @ 0x022a0b9c, 0x4 bytes, Thumb
 * func_ov111_022a0b98 @ 0x022a0b98, 0x4 bytes, Thumb
 * func_ov111_022a0b88 @ 0x022a0b88, 0x10 bytes, Thumb
 * func_ov111_022a0b70 @ 0x022a0b70, 0x16 bytes, Thumb
 */

extern void func_020ee470(void *argument0);
extern void func_ov111_0229fdf0(int);
extern int func_ov002_022080a8(int);

int func_ov111_022a0b9c(void)
{
    return 1;
}

int func_ov111_022a0b98(void)
{
    return 1;
}

int func_ov111_022a0b88(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

int func_ov111_022a0b70(int arg)
{
    func_ov111_0229fdf0(arg);
    func_ov002_022080a8(arg);
    return 1;
}
