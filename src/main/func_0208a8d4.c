/* func_0208a8d4 @ 0x0208a8d4, 0x6e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a8cc(void);

void func_0208a8d4(unsigned char *r0)
{
    unsigned char *p;
    int r1, r2;

    p = r0 + 0x59;
    if (*p == 0) {
        if (*(int *) (r0 + 0x38) > 2) {
            *(int *) (r0 + 0x48) += 6;
            p = r0 + 0x5a;
            if (*p != 0) {
                r2 = 6;
            } else {
                r1 = 5;
                r2 = ~r1;
            }
            *(int *) (r0 + 0x4c) += r2;
        } else {
            *(int *) (r0 + 0x48) -= 1;
            p = r0 + 0x5a;
            if (*p != 0) {
                r1 = 0;
                r2 = ~r1;
            } else {
                r2 = 1;
            }
            *(int *) (r0 + 0x4c) += r2;
        }
    }
    *(int *) (r0 + 0x38) -= 1;
    if (*(int *) (r0 + 0x38) > 0) {
        return;
    }
    *(int *) (r0 + 0x48) = 0;
    *(int *) (r0 + 0x4c) = 0;
    func_0208a8cc();
}
