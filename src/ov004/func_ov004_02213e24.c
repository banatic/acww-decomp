/* func_ov004_02213e24 @ 0x02213e24, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0203cfc8(unsigned int *object);
extern int func_020b9d3c(void *argument0, void *argument1, int argument2, void *argument3, int argument4, int argument5);
extern void func_ov004_0220d280(unsigned char *argument0, unsigned char argument1, int argument2);
extern void *data_ov004_022531c8;

int func_ov004_02213e24(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    func_ov004_0220d280((unsigned char *) (self + 0x740), (unsigned char) (0x1), (int) (0x0));
    v2 = *(int *) (self + 0x594);
    func_020b9d3c((void *) (self + 0x848), (void *) (v2), (int) (&data_ov004_022531c8),
                  (void *) (func_0203cfc8(*(unsigned int **) (self + 0x844))), (int) (0x0), (int) (0x0));
    return 0x1;
}
