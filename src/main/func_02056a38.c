/* func_02056a38 @ 0x02056a38, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056a64(void *);
extern void func_020b9ec4(void *);

void func_02056a38(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_02056a64(r4);
    func_020b9ec4((char *) r4 + 4);
}
