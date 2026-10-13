/* func_ov118_0229babc @ 0x0229babc, 0x44 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *p);
extern void func_ov118_0229a854(void *p);
extern int func_ov118_0229a460(void *p, unsigned int v);
extern void func_ov002_02208098(void *p, int v);

void func_ov118_0229babc(void *p)
{
    if (func_0208e484((char *) p + 0x6c0) != 0) {
        func_ov118_0229a854(p);
        if (func_ov118_0229a460(p, 0x800) != 0) {
            func_ov002_02208098(p, 0xa);
        } else {
            func_ov002_02208098(p, 3);
        }
    }
}
