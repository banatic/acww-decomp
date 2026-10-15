/* func_ov003_02228f54 @ 0x02228f54, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223c0d4;
void *func_02056578(void *p);
void *func_020551e0(void *p);
int func_0209d104(void *p);
void func_0209d340(void *p);

void *func_ov003_02228f54(char *self)
{
    *(int *) (self + 0x11c) = (int) &data_ov003_0223c0d4;
    func_02056578(self + 0x11c);
    func_020551e0(self + 0x58);
    func_0209d104(self + 8);
    func_0209d340(self + 4);
    return self;
}
