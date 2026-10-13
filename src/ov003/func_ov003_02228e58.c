/* func_ov003_02228e58 @ 0x02228e58, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020da13c;
extern int data_ov003_0223bfcc;
void func_0209d2b4(void *p);
void func_020ee62c(void *p);

void *func_ov003_02228e58(char *self)
{
    *(int *) self = (int) &data_ov003_0223bfcc;
    func_0209d2b4(self + 0x68);
    func_0209d2b4(self + 0x50);
    *(int *) self = (int) &data_020da13c;
    func_020ee62c(self);
    return self;
}
