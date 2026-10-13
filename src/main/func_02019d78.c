/* func_02019d78 @ 0x02019d78, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019d70(void *arg0, int arg1, int arg2);
extern void func_02019ea0(void *arg0);

void func_02019d78(void *arg0)
{
    void *r4;

    r4 = arg0;
    func_02019d70(r4, 0x16, 0);
    r4 = (void *) ((unsigned int) r4 + 0x2c);
    func_02019ea0(r4);
}
