/* func_0200f234 @ 0x0200f234, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208ffac(void);
extern int func_0208ff98(void);

void func_0200f234(int *arg0)
{
    int *r4;
    int r0;
    int r1;

    r4 = arg0;
    if (func_0208ffac() != 0) {
        r1 = 1;
        r0 = 0x170;
        *(int *) ((char *) r4 + r0) = r1;
    } else if (func_0208ff98() != 0) {
        r1 = 2;
        r0 = 0x170;
        *(int *) ((char *) r4 + r0) = r1;
    } else {
        r1 = 0;
        r0 = 0x170;
        *(int *) ((char *) r4 + r0) = r1;
    }
    return;
}
