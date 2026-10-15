/* func_02081c94 @ 0x02081c94, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02094f7c(void *);
extern void func_02081c70(void *, void *);
extern int func_020a8a70(void *, void *, int, int);
extern void *func_02094f64(void *);

void func_02081c94(void *param0, void *param1)
{
    unsigned char local[0x1c];

    func_02094f7c(local);
    func_02081c70(param0, local);
    func_020a8a70(param1, local, 0, 0);
    func_02094f64(local);
}
