/* func_020763f4 @ 0x020763f4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7948(void *);
extern void func_020736bc(void *, void *, int);
extern void func_020a7938(void *, void *);
extern void func_020a7408(void *, unsigned char);
extern void func_020a7944(void *);
extern void *data_020ccf94;

void func_020763f4(int a, int b, int c, void *d)
{
    unsigned char local[8];

    func_020a7948(local);
    func_020736bc(data_020ccf94, local, 1);
    func_020a7938(local, local + 1);
    func_020a7408(d, local[1]);
    func_020a7944(local);
}
