/* func_020b8cec @ 0x020b8cec, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e5848;
extern void func_020b91a0(void *);

void *func_020b8cec(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_020e5848;
    func_020b91a0((char *) self + 8);
    return self;
}
