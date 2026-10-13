/* func_0208f7f8 @ 0x0208f7f8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001cf4(int);
extern void func_02001bb4(int);
extern unsigned long long OS_GetTick(void);

void func_0208f7f8(void *r4)
{
    unsigned long long v;
    unsigned char *p;
    int r5;

    *(int *) ((char *) r4 + 0x20) = 1;
    *(int *) ((char *) r4 + 0x28) = 0;
    func_02001cf4(0x10);
    func_02001bb4(4);
    v = OS_GetTick();
    r5 = 1;
    *(int *) ((char *) r4 + 0x2c) = r5;
    *(unsigned long long *) ((char *) r4 + 0x30) = v + 0x1991bULL;
    p = (unsigned char *) r4 + 0x38;
    *p = (unsigned char) r5;
}
