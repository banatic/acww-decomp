/* func_ov003_02228cd4 @ 0x02228cd4, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0225f220;
extern int data_ov003_0225f278;
extern int data_ov003_0225f228;
extern int data_ov003_0225f224;
extern int data_ov003_0225f320[];
void func_0205502c(void *p, int k);
void func_02055454(void *p);
void func_0209d090(void *p);
void func_0209d200(void *p, void *q);

void func_ov003_02228cd4(char *self)
{
    data_ov003_0225f220 = 0;
    func_0205502c(&data_ov003_0225f278, 0);
    func_02055454(&data_ov003_0225f278);
    func_0209d090(&data_ov003_0225f228);
    func_0209d200(self + 0x68, &data_ov003_0225f224);
    data_ov003_0225f320[13] = 0;
    data_ov003_0225f320[14] = 0;
}
