/* func_02037278 @ 0x02037278, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020371f0(void *);
extern void func_02037190(void *);

void func_02037278(void *param)
{
    void *r4 = param;
    func_020371f0(r4);
    *(unsigned int *) ((char *) r4 + 8) = 0x18;
    func_02037190(r4);
    *(unsigned char *) ((char *) r4 + 0xf) = 0;
    *(unsigned char *) ((char *) r4 + 0x10) = 0;
}
