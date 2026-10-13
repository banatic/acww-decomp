/* func_ov090_022991e0 @ 0x022991e0, 0x78 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002d14(void *, int, int, int, int, int);
extern void func_02064af4(void *, void *, int);
extern int func_0206fca4(void);
extern void func_ov090_02298fac(void *, int);
extern void func_02001c08(int);

extern int data_ov090_02299914[];
extern int data_ov090_02299928[];
extern int data_ov090_0229993c[];
extern int data_021fbe94;

void func_ov090_022991e0(unsigned char *param)
{
    func_02002d14(data_ov090_02299914, data_021fbe94, 8, 0xf, 0xf, 0xf);
    func_02064af4(data_ov090_02299928, param + 0x144, 0x800);
    func_02064af4(data_ov090_0229993c, param + 0x944, 0x800);
    {
        int result = func_0206fca4();
        func_ov090_02298fac(param, result);
    }
    param[0x91] = 1;
    param[0x92] = 0;
    param[0x8c] = 1;
    func_02001c08(0);
}
