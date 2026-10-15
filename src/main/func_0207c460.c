/* func_0207c460 @ 0x0207c460, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003704(void *param1);
extern int func_0207cf14(void *param1, void *param2);
extern int func_0207cf74(unsigned int);
extern unsigned char *func_0207c498(void *param1, signed char param2);

void func_0207c460(void *param1, void *param2)
{
    signed char local;
    void *r4;
    void *r5;

    r4 = param1;
    r5 = param2;

    if (func_02003704(r5) != 0) {
        r5 = (void *) func_0207cf14(r4, r5);
        if (func_0207cf74((unsigned int) r5) != 0) {
            local = (signed char) ((int) r5 & 0xff);
            func_0207c498(r4, local);
        }
    }
}
