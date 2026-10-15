/* func_ov118_0229b868 @ 0x0229b868, 0x48 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208e95c(int, int);
extern void func_ov118_0229aa0c(int);
extern void func_ov002_02207fc0(int);
extern int func_ov118_0229a460(int, int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);

void func_ov118_0229b868(int r0)
{
    func_0208e95c(r0 + 0x678, 1);
    func_ov118_0229aa0c(r0);
    func_ov002_02207fc0(r0);
    if (func_ov118_0229a460(r0, 0x800) != 0) {
        func_ov002_02208098(r0, 10);
    } else {
        func_ov002_02208098(r0, 3);
    }
}
