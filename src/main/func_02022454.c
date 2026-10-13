/* func_02022454 @ 0x02022454, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int p);
extern int func_020036e8(int p);
extern void func_0202da38(char *a, char *b, char *c, int d, int e, int f, int g, int h, int i);
extern void func_0202bd7c(char *a, int b, unsigned char c);
extern int data_020c8cc0;
extern unsigned char data_020c8960[];

int func_02022454(char *self)
{
    int i;
    func_0202da38(self, self + 0x104, self + 0x122, 0x1e,
                  func_020036e8(func_0208150c(*(int *) (*(int *) (self + 0x100) + 0x830))), data_020c8cc0,
                  *((unsigned char *) &data_020c8cc0 + 4), 0, 0);
    for (i = 0; i < 6; i++) {
        func_0202bd7c(self, i, data_020c8960[i]);
    }
    return 1;
}
