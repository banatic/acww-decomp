/* func_ov047_02260d28 @ 0x02260d28, 0x94 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
void func_ov047_02260d28(unsigned char *p)
{
    unsigned char *ptr;
    unsigned char *ptr3;
    unsigned int *ptr2;
    if (p[0x1e] == 0x32) {
        int cond;
        unsigned short local;
        unsigned short value;
        int inRange;
        int delta;
        if (func_0204bcdc(p + 0xce)) {
            int call1;
            int call2;
            local = 0xfff1;
            call1 = func_0204bc64(p + (0xce & 0xFFFF));
            call2 = func_0204bc64(&local);
            cond = (call1 == call2) ? (1) : (0);
        } else {
            cond = ((*((unsigned short *) (p + 0xce))) == 0xfff1) ? (1) : (0);
        }
        if (cond) {
            return;
        }
        ptr = p + 0xce;
        inRange = 0;
        value = *((unsigned short *) ptr);
        if ((value >= 0x12b0) && (value <= 0x12e7)) {
            inRange = 1;
        }
        ptr3 = p;
        if (inRange) {
            delta = value - 0x12b0;
        } else {
            cond = ((*((unsigned short *) (p + 0xce))) == 0xfff1) ? (1) : (0);
            delta = -1;
        }
        delta = delta + 0x6e;
        ptr2 = (unsigned int *) (ptr3 + 0xd0);
        *ptr2 = (unsigned char) delta;
    }
}
