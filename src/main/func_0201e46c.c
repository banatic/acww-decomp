/* func_0201e46c @ 0x0201e46c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02021118(void *);
extern void func_0202213c(void *);
extern void func_0202dac0(void *);

void func_0201e46c(void *param0, void *param1)
{
    unsigned char *r5;
    unsigned char *r4;
    unsigned char *r0;

    r5 = param0;
    r4 = param1;
    func_02021118(r5);
    func_0202213c(r5);
    r0 = r5 + 0x104;
    *(unsigned int *) r4 = (unsigned int) r0;
    r0 = r5 + 0x122;
    r4[4] = *r0;
    func_0202dac0(r5);
}
