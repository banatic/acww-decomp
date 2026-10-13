/* func_ov118_0229bb48 @ 0x0229bb48, 0x2c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229c554(void *);
extern int func_ov002_02209f64(void *);
extern int func_ov002_02208098(void *, unsigned char);

void func_ov118_0229bb48(void *r0)
{
    if (func_ov002_02209f64((char *) r0 + 0x6c0) == 0) {
        func_ov002_02208098(r0, *(unsigned char *) ((char *) r0 + 0xab));
        func_ov118_0229c554(r0);
    }
}
