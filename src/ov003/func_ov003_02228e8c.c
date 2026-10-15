/* func_ov003_02228e8c @ 0x02228e8c, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020da13c;
extern int data_ov003_0223bfcc;
void *func_020ee660(void *p);
void func_0209d2b8(void *p);

void *func_ov003_02228e8c(char *self)
{
    func_020ee660(self);
    *(int *) self = (int) &data_020da13c;
    *(int *) self = (int) &data_ov003_0223bfcc;
    func_0209d2b8(self + 0x50);
    func_0209d2b8(self + 0x68);
    *(int *) (self + 0x80) = 0;
    return self;
}
