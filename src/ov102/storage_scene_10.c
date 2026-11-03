/* storage_scene_10: 2 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229e890 @ 0x0229e890, 0x20 bytes, Thumb
 * func_ov102_0229e874 @ 0x0229e874, 0x1a bytes, Thumb
 */

extern void func_ov102_0229e130(void *obj);
extern void func_ov002_02208090(void *obj, int flag);
extern unsigned char *func_ov002_022080a0(void *obj, unsigned char value);
extern int func_020ee45c(int param);
extern void func_ov092_0229929c(int param);
extern void func_ov102_0229e108(int param);

int func_ov102_0229e890(void *obj)
{
    func_ov102_0229e130(obj);
    func_ov002_02208090(obj, 0);
    func_ov002_022080a0(obj, 0);
    return 1;
}

int func_ov102_0229e874(int param)
{
    func_ov092_0229929c(func_020ee45c(param));
    func_ov102_0229e108(param);
    return 1;
}
