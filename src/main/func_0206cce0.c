/* func_0206cce0 @ 0x0206cce0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050c48(void);
extern int func_020a9334(int, int);

int func_0206cce0(int arg0)
{
    int r4;
    int r0;
    int r1;

    r4 = arg0;
    r0 = func_02050c48();
    r1 = r0;
    r0 = r4;
    func_020a9334(r0, r1);
    return;
}
