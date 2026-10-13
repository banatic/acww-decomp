/* func_ov102_0229e4f4 @ 0x0229e4f4, 0x54 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov102_0229dfa4(void);
extern void func_02002708(int);
extern int func_ov002_02207f20(int, int, int, int, int);
extern int func_ov002_02207e90(int, int);
extern int func_ov102_0229c298(int, int);
extern int func_ov002_02207e80(int, int, int, int);
extern int func_ov002_02207f60(int);

void func_ov102_0229e4f4(int r0)
{
    int r4 = r0;
    int sp0;
    int result;

    func_ov102_0229dfa4();
    sp0 = 0x30;
    func_ov002_02207f20(r4, 2, 0, 1, sp0);
    func_ov002_02207e90(r4, 0x90);
    func_ov102_0229c298(r4, 0x80);
    func_02002708(4);
    func_ov002_02207e80(r4, 4, 0, 0);
    result = func_ov002_02207f60(r4);
    *(int *) ((char *) r4 + 0x24d4) = result;
}
