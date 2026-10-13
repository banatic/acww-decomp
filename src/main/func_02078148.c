/* func_02078148 @ 0x02078148, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020780f0(void *self, int arg);

unsigned char *func_02078148(unsigned char *self)
{
    unsigned char count = *((unsigned char *) self + 0xb7e);
    if (count < 15) {
        *((unsigned char *) self + 0xb7e) = count + 1;
        return self + 196 * (*((unsigned char *) self + 0xb7e) - 1);
    } else {
        func_020780f0(self, 0);
        *((unsigned char *) self + 0xb7e) = 15;
        return self + 196 * (*((unsigned char *) self + 0xb7e) - 1);
    }
}
