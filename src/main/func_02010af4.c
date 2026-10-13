/* func_02010af4 @ 0x02010af4, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d7b8(void *p, int a, int b, int c);
extern int func_0205d894(void *p);
extern void func_0205678c(void *p, int a, int b, int c, int d, int e);
extern void func_02056778(void *p);

void func_02010af4(void *self, int *src, unsigned char *byte)
{
    func_0205d7b8((char *) self + 0x70e, *src, 1, 0);
    func_0205678c((char *) self + 0x73c, func_0205d894((char *) self + 0x70e), 0, 0, *byte, 0x1000);
    func_02056778((char *) self + 0x73c);
    *(int *) ((char *) self + 0x770) = *src;
}
