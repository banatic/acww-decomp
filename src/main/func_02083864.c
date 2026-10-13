/* func_02083864 @ 0x02083864, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083c78(void *);
extern void func_020edb3c(void *);
extern void func_02083910(void);
extern void func_02138c48(void *, int, int, void (*)(void));

extern unsigned char data_020e1b1c[];

void *func_02083864(void *obj)
{
    void *p;

    *(void **) obj = (void *) data_020e1b1c;
    p = obj;
    p = (char *) p + 8;
    func_02138c48(p, 4, 8, func_02083910);
    func_02083c78(obj);
    func_020edb3c(obj);
    return obj;
}
