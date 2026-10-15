/* func_ov086_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov086_02278eb0(void *);
extern void *func_0202ee5c(void *);
extern char data_ov086_0227938c;

void *func_ov086_02278a00(void *p)
{
    *(void **) p = &data_ov086_0227938c;
    func_ov086_02278eb0((char *) p + 0x658);
    func_0202ee5c(p);
    return p;
}
