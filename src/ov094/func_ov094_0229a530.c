/* func_ov094_0229a530 @ 0x0229a530, 0xd0 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088d9c(int a);
extern int func_02088d94(int a);
extern int func_ov094_0229ab7c(unsigned char *p, int a);
extern int func_ov094_0229ab68(unsigned char *p);
extern int func_ov094_0229a328(unsigned char *p, int a);
extern int func_ov094_0229a668(unsigned char *p, int a, int b);
extern int func_ov094_0229a8bc(unsigned char *p, unsigned char a);
extern int func_020896b8(int a, int b, int c, int d, int e, unsigned int f, int g);
extern void func_ov094_0229a634(unsigned char *p, int a, int b, int c);
extern int func_ov094_0229a600(unsigned char *p, int a, int b);

void func_ov094_0229a530(unsigned char *p0, int p1, int p2, int p3, int p4)
{
    int x = func_02088d9c(p1) + p3;
    int y = func_02088d94(p1) + p4;
    int z = 0;

    if (func_ov094_0229ab7c(p0, p2) != 0) {
        z = func_ov094_0229ab68(p0);
        x += z;
        y += z;
    }

    if (func_ov094_0229a328(p0 + 0xa40, p2) != 0) {
        func_ov094_0229a668(p0, x, y);
    }

    if (func_ov094_0229a328(p0 + 0xa38, p2) != 0) {
        int var = -1;

        if (func_ov094_0229a8bc(p0, (unsigned char) p2) != 0) {
            var = 0xe;
        }

        func_020896b8(1, p1, p3 + z, p4 + z, var, *(unsigned int *) (p0 + 0xa50), 0);
        func_ov094_0229a634(p0, x, y, var);

        if (func_ov094_0229ab7c(p0, p2) != 0) {
            func_ov094_0229a600(p0, x, y);
        }
    }
}
