/* func_0207f120 @ 0x0207f120, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern int func_0207f1c8(int);
extern void *func_0209b5ec(void *);
extern int func_0209c330(unsigned char *);

int func_0207f120(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    result = func_02003704((void *) func_0208150c(arg0));
    if (result != 0) {
        if (func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(r4))) == 9) {
            return 1;
        }
    }
    return 0;
}
