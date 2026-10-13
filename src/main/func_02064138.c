/* func_02064138 @ 0x02064138, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a887c(void *p);
extern __arm void func_020edb3c(void *p);
extern unsigned char data_020de67c;

void *func_02064138(void *p)
{
    *(void **) p = &data_020de67c;
    func_020a887c(p);
    func_020edb3c(p);
    return p;
}
