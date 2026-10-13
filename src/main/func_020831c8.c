/* func_020831c8 @ 0x020831c8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e1b00;
extern void func_02083294(void);
extern void __arm func_02138c48(void *, int, int, void (*)(void));
extern void __arm func_020edb3c(void *);
extern void func_02083c78(void *);

void *func_020831c8(void *param)
{
    *(void **) param = &data_020e1b00;
    func_02138c48((char *) param + 8, 5, 0x6c, func_02083294);
    func_02083c78(param);
    func_020edb3c(param);
    return param;
}
