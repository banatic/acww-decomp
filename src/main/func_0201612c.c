/* func_0201612c @ 0x0201612c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066974(void *);
extern void func_02016004(void *);
extern void func_020159f0(void *);

void func_0201612c(void *arg0)
{
    void *r4 = arg0;
    func_02066974(r4);
    *(unsigned int *) ((char *) r4 + 0x48) = 0;
    *(unsigned int *) ((char *) r4 + 0x50) = 0;
    *(unsigned char *) ((char *) r4 + 0x54) = 0;
    *(unsigned char *) ((char *) r4 + 0x55) = 0;
    *(unsigned int *) ((char *) r4 + 0x5c) = 0;
    func_02016004(r4);
    func_020159f0(r4);
}
