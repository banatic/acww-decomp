/* func_ov048_02262378 @ 0x02262378, 0x16 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_02068358(void *p);
extern void func_02068434(void *p);

void func_ov048_02262378(void *self)
{
    void *p = *(void **) ((char *) self + 0x40);
    func_02068358(p);
    func_02068434(p);
}
