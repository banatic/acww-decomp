/* func_0207dd84 @ 0x0207dd84, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02079350(int);
extern int func_0208150c(int);
extern int func_0207cf14(int *, int);
extern int func_02003704(int);
extern int data_021e5a2c;

int func_0207dd84(int a)
{
    int r4 = *(signed char *) ((char *) func_02079350(a) + 0x160);
    int r1 = func_0208150c(a);
    int r6 = func_0207cf14(&data_021e5a2c, r1);
    int cond1 = func_02003704(func_0208150c(a));
    if (cond1 != 0 && r4 != -1 && r6 == r4) {
        return 1;
    } else {
        return 0;
    }
}
