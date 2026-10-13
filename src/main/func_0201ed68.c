/* func_0201ed68 @ 0x0201ed68, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(int x);
extern int func_020036e8(void);
extern void func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern int data_020c8ba0;

void func_0201ed68(void *p1, void *p2)
{
    int a;
    int b;
    func_0208150c(*(int *) ((char *) *(void **) ((char *) p1 + 0x100) + 0x830));
    a = func_020036e8();
    b = data_020c8ba0;
    func_0202da38(p1, (char *) p1 + 0x104, (char *) p1 + 0x122, 30, a, b, 1, 0xF, 2);
    *(void **) p2 = (char *) p1 + 0x104;
    ((unsigned char *) p2)[4] = ((unsigned char *) p1)[0x122];
}
