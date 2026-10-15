/* func_02033614 @ 0x02033614, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int *func_0203394c(void *buf, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8);
extern void *func_0203364c(void *a1, void *buf);
extern void *func_020339b8(void *buf);

void *func_02033614(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8)
{
    unsigned char buf[48];
    void *result;

    func_0203394c(buf, a2, a3, a4, a5, a6, a7, a8);
    result = func_0203364c(a1, buf);
    func_020339b8(buf);
    return result;
}
