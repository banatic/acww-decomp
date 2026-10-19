/* func_0208bd18 @ 0x0208bd18, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208c630(void *param1, int param2);
extern void func_020a7e64(void);
extern void func_020a7e70(void);
extern void func_0200467c(int param1);

void func_0208bd18(void *param0)
{
    unsigned char *r4;
    unsigned char temp;

    r4 = (unsigned char *) param0;
    *(unsigned int *) (r4 + 0x20) = 3;
    func_0208c630(r4 + 0x28, 1);
    *(r4 + 0x24) = 1;
    temp = *(r4 + 0x25);
    if (temp != 0) {
        func_020a7e64();
    } else {
        func_020a7e70();
    }
    func_0200467c(0x4a);
}
