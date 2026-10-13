/* func_0208c260 @ 0x0208c260, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f0(void *elem, void *data);
extern void func_0208a1ec(void *elem, int flag);
extern void func_0208a144(void *elem);
extern unsigned char data_020d5b3c[];

void func_0208c260(void *arg0)
{
    int i;
    char *base;
    char *elem;

    *((int *) ((char *) arg0 + 0xc0)) = 3;
    i = 0;
    base = (char *) arg0;
    base += 0x0c;

    for (; i < 9; i++) {
        elem = base + i * 20;
        func_0208a1f0(elem, &data_020d5b3c[(i + 0x17) * 8]);
        func_0208a1ec(elem, 1);
        func_0208a144(elem);
    }
}
