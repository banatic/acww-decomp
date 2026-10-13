/* func_02035684 @ 0x02035684, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020374d0(void *dst, int a, int mask, int b, int c, int d);
extern void func_02035198(void *src, void *buf);
extern void func_020374cc(void *buf);
extern void *data_021c526c;

void func_02035684(int param0, int param1, int param2)
{
    int buf[7];
    func_020374d0(buf, param0, 0xffff, 0, param1, 0);
    if (param2 > 0) {
        buf[6] = param2;
    }
    func_02035198(data_021c526c, buf);
    func_020374cc(buf);
}
