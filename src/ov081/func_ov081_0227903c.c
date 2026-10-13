/* func_ov081_0227903c @ 0x0227903c, 0x24 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *self);
extern int data_ov081_0227972c;

void *func_ov081_0227903c(void *self)
{
    char *p;
    func_0202eb70(self);
    *((unsigned int *) self) = (unsigned int) &data_ov081_0227972c;
    p = (char *) self;
    p += 0xc4;
    *((unsigned short *) p) = 0xfff1;
    return self;
}
