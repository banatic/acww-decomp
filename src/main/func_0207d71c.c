/* func_0207d71c @ 0x0207d71c, 0x6a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern void *func_0207f1c8(void *);
extern void *func_0209b5e8(int);
extern void *func_0209b91c(void *);
extern int func_0209bd44(void *);
extern int func_0209bd04(void *);
extern int func_0209bba0(void *);
extern int func_0209bc40(void *);
extern void func_0207dcf4(void *);
extern void func_0209baf4(void *);
extern void *func_0209b5ec(void *);
extern void func_0209c270(unsigned char *);

void func_0207d71c(void *p)
{
    void *r6;
    void *r7;
    void *r4;

    if (func_02003704((void *) func_0208150c((unsigned int) p)) != 0) {
        r6 = func_0207f1c8(p);
        r7 = func_0209b5e8((int) r6);
        r4 = func_0209b91c((void *) r7);
        if (func_0209bd44(r4) != 0) {
            if (func_0209bd04(r4) == 0) {
                if (func_0209bba0(r4) == 3) {
                    if (func_0209bc40(r4) == 4) {
                        func_0207dcf4(p);
                    }
                    func_0209baf4(r7);
                    func_0209c270((unsigned char *) func_0209b5ec(r6));
                }
            }
        }
    }
}
