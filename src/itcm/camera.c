/* camera: 2 functions, module itcm
 * mwccarm 1.2/base -O4,s
 * func_01ffcbb0 @ 0x01ffcbb0, 0x28 bytes, Thumb
 * func_01ffcb9c @ 0x01ffcb9c, 0x14 bytes, Thumb
 */

extern void func_01ffd070(void *, void *, void *);

void func_01ffcb9c(int a, int b);

void func_01ffcbb0(void *a, void *b)
{
    char buf[12];
    func_01ffcb9c((int) buf, (int) (b));
    func_01ffd070(a, (char *) b + 0x15c, buf);
}

void func_01ffcb9c(int a, int b)
{
    func_01ffd070((void *) a, (void *) (b + 0x150), (void *) (b + 0x84));
}
