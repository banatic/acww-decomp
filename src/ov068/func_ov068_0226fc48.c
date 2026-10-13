/* func_ov068_0226fc48 @ 0x0226fc48, 0x74 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int data_020c904c;
extern int FX_Div(int, int);
extern void func_020912d4(int, int *, int, short *);
extern void func_020044c0(void *, int, int, int);
extern void func_ov003_02228400(void *, int);

void func_ov068_0226fc48(void *p)
{
    struct {
        short a;
        int b;
        int c;
        int d;
    } local;

    local.b = *(int *) ((char *) p + 0x5c);
    local.c = *(int *) ((char *) p + 0x60);
    local.d = *(int *) ((char *) p + 0x64);
    local.c = data_020c904c + 0x100;
    local.a = (short) FX_Div(*(int *) ((char *) p + 0x26c), 0x1000);
    func_020912d4(0x3f, &local.b, 0, &local.a);
    func_020044c0((char *) p + 0x328, 0x821, 0x7f, 0);
    func_ov003_02228400((char *) p + 0x5c, 0x5000);
}
