/* public_box_states_5: 2 functions, module ov110
 * mwccarm 1.2/base -O4,s
 * func_ov110_0229ead0 @ 0x0229ead0, 0x20 bytes, Thumb
 * func_ov110_0229eab4 @ 0x0229eab4, 0x1a bytes, Thumb
 */

extern void func_ov110_0229e3c4(void *);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_020ee45c(void *argument0);
extern void func_ov092_0229929c(void *argument0);
extern void func_ov110_0229e38c(int);

int func_ov110_0229ead0(void *p)
{
    func_ov110_0229e3c4(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 0);
    return 1;
}

int func_ov110_0229eab4(int param)
{
    int r4 = param;

    func_ov092_0229929c((void *) func_020ee45c((void *) param));
    func_ov110_0229e38c(r4);
    return 1;
}
