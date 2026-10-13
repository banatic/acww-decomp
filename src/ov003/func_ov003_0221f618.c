/* func_ov003_0221f618 @ 0x0221f618, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205577c(void *p);
extern void func_02138d6c(void *p, int a, int b, void (*func1)(void), void (*func2)(void));
extern void func_020565b0(void);
extern void func_020565c8(void);

void *func_ov003_0221f618(void *this)
{
    func_0205577c(this);
    func_02138d6c((char *) this + 0xb4, 2, 0x20, func_020565c8, func_020565b0);
    *((int *) ((char *) this + 0xac)) = -1;
    *((int *) ((char *) this + 0xb0)) = -1;
    *((int *) ((char *) this + 0x9c)) = 0;
    *((int *) ((char *) this + 0xa0)) = 0;
    *((int *) ((char *) this + 0xa4)) = 0;
    return this;
}
