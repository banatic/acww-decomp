/* func_02079238 @ 0x02079238, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_02079350(void);
extern int func_0207944c(unsigned char *);
extern void func_02079438(void *);

void func_02079238(void)
{
    unsigned char *p;
    int i;
    p = func_02079350();
    for (i = 0; i < 8; i++) {
        func_02079438((void *) func_0207944c(p));
        p += 0x2c;
    }
}
