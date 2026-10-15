/* func_ov144_0229ac90 @ 0x0229ac90, 0x94 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern int func_02002c6c(void *data, int obj, int type, int a4, int a5, int a6);
extern int func_02002d14(void *data, int obj, int type, int a4, int a5, int a6);
extern int func_02064af4(void *src, void *dst, int size);
extern void func_ov144_02299b7c(void *param);

extern unsigned char data_ov144_0229b480[];
extern unsigned char data_ov144_0229b494[];
extern unsigned char data_ov144_0229b4a8[];
extern unsigned char data_ov144_0229b4bc[];
extern unsigned char data_ov144_0229b4d0[];

void func_ov144_0229ac90(void *param)
{
    int local = data_021fbe94;

    func_02002c6c((void *) data_ov144_0229b480, local, 6, 17, 17, 152);
    func_02002c6c((void *) data_ov144_0229b494, local, 6, 0x26e, 0x26e, 0x27e);
    func_02002d14((void *) data_ov144_0229b4a8, local, 6, 1, 1, 0xa);
    func_02064af4((void *) data_ov144_0229b4bc, (char *) param + 0x90a, 0x800);
    func_02064af4((void *) data_ov144_0229b4d0, (char *) param + 0x190a, 0x800);
    func_ov144_02299b7c(param);
}
