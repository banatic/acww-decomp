/* func_ov145_02299fec @ 0x02299fec, 0x24 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov145_0229a06c(void *a, void *b, int c, int d);

void func_ov145_02299fec(void *self)
{
    unsigned short *p;
    p = (unsigned short *) ((char *) self + 0xba);
    *p = (unsigned short) func_ov145_0229a06c(self, (char *) self + 0xbac, 0x12e8, 0x38);
}
