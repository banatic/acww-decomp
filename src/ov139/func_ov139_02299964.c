/* func_ov139_02299964 @ 0x02299964, 0x60 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern int func_02002c6c(void *, void *, int, int, int, int);
extern int func_02002d14(void *, void *, int, int, int, int);

extern unsigned char data_ov139_02299e00[];
extern unsigned char data_ov139_02299e14[];
extern unsigned char data_ov139_02299e28[];

void func_ov139_02299964(void)
{
    void *obj = data_021fbe94;
    func_02002c6c((void *) data_ov139_02299e00, obj, 8, 0x80, 0x80, 0xff);
    func_02002c6c((void *) data_ov139_02299e14, obj, 8, 0x160, 0x160, 0x1ff);
    func_02002d14((void *) data_ov139_02299e28, obj, 8, 4, 4, 0xd);
}
