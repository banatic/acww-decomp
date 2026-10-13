/* func_ov068_0226af70 @ 0x0226af70, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern void func_0201cc48(void *);
extern void func_0203e020(void *);
extern void func_0201ce5c(void *, int);
extern void func_0201ce44(void *, int);

void func_ov068_0226af70(unsigned char *arg0, char *arg1)
{
    if (func_02014868((char *) arg1 + 0x618) != 0) {
        return;
    }
    func_0201cc48((char *) arg1 + 0x83c);
    func_0203e020((char *) arg1);
    func_0201ce5c((char *) arg1, 0);
    func_0201ce44((char *) arg1, 0);
    arg0[0x1c] = 1;
}
