/* func_ov003_02228f8c @ 0x02228f8c, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223c0d4;
void func_0209d34c(void *p);
void func_0209d11c(void *p);
void func_02055210(void *p);
void func_020565ec(void *p);
void func_0209d0a4(void *p);

void *func_ov003_02228f8c(char *self)
{
    func_0209d34c(self + 4);
    func_0209d11c(self + 8);
    func_02055210(self + 0x58);
    func_020565ec(self + 0x11c);
    *(int *) (self + 0x11c) = (int) &data_ov003_0223c0d4;
    *(int *) self = 0;
    func_0209d0a4(self + 8);
    return self;
}
