/* func_02080d70 @ 0x02080d70, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void *);
extern int func_02003704(void);
extern void *func_02098844(void *, int);
extern void func_02099870(void);
extern int func_020951bc(void);
extern void func_02080dc0(void *, void *);
extern unsigned char data_021dc7bc[1];

void func_02080d70(void *param)
{
    int i;
    void *x;

    func_0208150c(param);
    if (func_02003704() != 0) {
        if ((unsigned int) &data_021dc7bc != 0) {
            for (i = 0; i < 4; i++) {
                x = func_02098844((void *) &data_021dc7bc, i);
                if (x != 0) {
                    func_02099870();
                    if (func_020951bc() != 0) {
                        func_02080dc0(param, x);
                    }
                }
            }
        }
    }
}
