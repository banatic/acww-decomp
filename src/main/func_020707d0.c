/* func_020707d0 @ 0x020707d0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a88ec(void *p);
extern char data_020e1784;

void *func_020707d0(void *p)
{
    func_020a88ec(p);
    *(void **) p = &data_020e1784;
    return p;
}
