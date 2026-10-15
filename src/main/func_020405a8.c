/* func_020405a8 @ 0x020405a8, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern int func_0207f150(int);
extern int func_0207f294(int);

int func_020405a8(int r0, int r1)
{
    int r4 = 0;
    int r5 = r0;
    int r6 = r1;

    if (func_02003704((void *) func_0208150c(r0)) != 0) {
        if (func_0207f150(r5) == 3) {
            int r0 = func_0207f294(r5);
            int r1 = ~r4;
            if (r0 != r1 && r0 != r6) {
                r4 = 1;
            }
        }
    }
    return r4;
}
