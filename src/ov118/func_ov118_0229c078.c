/* func_ov118_0229c078 @ 0x0229c078, 0x1e bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov118_0229b664(void);
extern void func_020b9ccc(void *);

void func_ov118_0229c078(void *param)
{
    void *p;
    func_ov118_0229b664();
    p = (char *) param + 0xb4;
    func_020b9ccc(p);
    p = (char *) param + 0xd8;
    func_020b9ccc(p);
}
