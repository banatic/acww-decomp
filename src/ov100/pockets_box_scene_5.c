/* pockets_box_scene_5: 2 functions, module ov100
 * mwccarm 1.2/base -O4,s
 * func_ov100_0229eacc @ 0x0229eacc, 0x20 bytes, Thumb
 * func_ov100_0229eab0 @ 0x0229eab0, 0x1a bytes, Thumb
 */

extern void func_ov100_0229e400(int);
extern void func_ov002_02208090(int, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov100_0229e3cc(int a);
extern void func_ov092_0229929c(void *argument0);
extern int func_020ee45c(void *argument0);

int func_ov100_0229eacc(int p)
{
    func_ov100_0229e400(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 0);
    return 1;
}

int func_ov100_0229eab0(int a)
{

    func_ov092_0229929c((void *) func_020ee45c((void *) a));
    func_ov100_0229e3cc(a);
    return 1;
}
