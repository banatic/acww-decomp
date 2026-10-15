/* func_ov004_02222554 @ 0x02222554, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222271c(void *self);
extern int func_0208150c(int a);
extern int func_0200366c(int a, void *b, int c, void *d);
extern int func_ov004_022226f8(void *self);
extern int func_020644cc(int a);
extern int data_ov004_02257f9c;
extern int data_ov004_022542b0;
extern int data_ov004_022542bc;

void func_ov004_02222554(char *self, char *out)
{
    char *h;

    *(int *) out = (int) &data_ov004_02257f9c;
    func_ov004_0222271c(self);
    h = *(char **) (self + 0x1a8);
    if (*(unsigned char *) (h + 0x897) == 0) {
        func_0200366c(func_0208150c(*(int *) (h + 0x830)), &data_ov004_02257f9c, 0x28, &data_ov004_022542b0);
    } else {
        func_0200366c(func_0208150c(*(int *) (h + 0x830)), &data_ov004_02257f9c, 0x28, &data_ov004_022542bc);
    }
    *(char *) (*(char **) (self + 0x1a8) + 0x899) = 0;
    if (func_ov004_022226f8(self) != 0) {
        out[4] = (char) (func_020644cc(3) + 3);
        *(char *) (*(char **) (self + 0x1a8) + 0x898) = 1;
    } else {
        out[4] = (char) func_020644cc(3);
        *(char *) (*(char **) (self + 0x1a8) + 0x898) = 0;
    }
}
