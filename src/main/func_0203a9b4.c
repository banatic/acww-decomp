/* func_0203a9b4 @ 0x0203a9b4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *);
extern char data_020da70c[];

void *func_0203a9b4(void *p)
{
    *(void **) p = &data_020da70c;
    func_020edb3c(p);
    return p;
}
