/* func_ov003_02228d1c @ 0x02228d1c, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0225f220;
extern int data_ov003_0225f224;
extern int data_ov003_0225f228;
void *func_0209d238(void *p, void *q);
void func_0209d0a4(void *p);

int func_ov003_02228d1c(char *self)
{
    data_ov003_0225f220 = 2;
    func_0209d238(self + 0x68, &data_ov003_0225f224);
    func_0209d0a4(&data_ov003_0225f228);
    return 1;
}
