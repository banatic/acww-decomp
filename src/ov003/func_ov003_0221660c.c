/* func_ov003_0221660c @ 0x0221660c, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int func_02073908(unsigned int, unsigned int);
extern int func_0200f290(void *, int);
extern void func_ov003_02216520(void *);

void func_ov003_0221660c(void *p)
{
    if (func_02073908(data_020ccf94, *(unsigned int *) ((char *) p + 0x800)) != 0) {
        return;
    }
    if (func_0200f290(p, 0x1c) == 0) {
        return;
    }
    func_ov003_02216520(p);
}
