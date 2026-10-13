/* func_01ffcbb0 @ 0x01ffcbb0, 0x28 bytes, Thumb, module itcm
 * mwccarm 1.2/base -O4,s
 */

extern void func_01ffcb9c(void *);
extern void func_01ffd070(void *, void *, void *);

void func_01ffcbb0(void *a, void *b)
{
    char buf[12];
    func_01ffcb9c(buf);
    func_01ffd070(a, (char *) b + 0x15c, buf);
}
