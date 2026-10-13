/* func_02062ca4 @ 0x02062ca4, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206e71c(void *);
extern void func_0206e808(void *);

void func_02062ca4(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_0206e71c(r4);
    r4 = (char *) r4 + 0x54;
    func_0206e808(r4);
}
