/* func_0207dd1c @ 0x0207dd1c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02079350(void);
extern int func_0208150c(int);
extern int func_0207cf14(int, int);
extern int func_02003704(int);

extern unsigned char data_021e5a2c[];

int func_0207dd1c(int param)
{
    int r4;
    int r6;
    int r0;
    int r1;
    int r5 = param;
    r0 = func_02079350();
    r4 = ((signed char *) r0)[0x161];
    r0 = func_0208150c(r5);
    r1 = r0;
    r0 = func_0207cf14((unsigned int) data_021e5a2c, r1);
    r6 = r0;
    r0 = func_0208150c(r5);
    r0 = func_02003704(r0);
    if (r0 != 0) {
        if (r6 == r4) {
            return 1;
        }
    }
    return 0;
}
