/* func_02034d28 @ 0x02034d28, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02035494(void *p);
extern void func_020ee62c(void *p);
extern void func_020edf54(void *p);
extern int data_020da334[];
extern int data_020da13c[];

void *func_02034d28(void *p)
{
    *(void **) p = (void *) &data_020da334;
    func_02035494((char *) p + 0x50);
    *(void **) p = (void *) &data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
