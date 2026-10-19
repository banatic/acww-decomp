/* func_ov083_02278dd0 @ 0x02278dd0, 0x38 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);

int func_ov083_02278dd0(void *self)
{
    int r1 = func_02016104((char *) self + 0x65c);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}
