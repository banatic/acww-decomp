/* func_ov142_0229b174 @ 0x0229b174, 0x44 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern void func_ov002_02208090(void *p, int n);
extern int func_ov142_02299668(void *p, int n);
extern int func_ov142_02299648(void *p, int n);
extern void func_ov004_0223d03c(void);
extern void func_ov004_0223d064(void);

void func_ov142_0229b174(void *p)
{
    unsigned int flag;
    func_ov002_02208090(p, 2);
    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag > 0) {
        if (func_ov142_02299668(p, 0x40) != 0) {
            func_ov142_02299648(p, 0x40);
            func_ov004_0223d03c();
            func_ov004_0223d064();
        }
    }
}
