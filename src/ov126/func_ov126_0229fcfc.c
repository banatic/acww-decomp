/* func_ov126_0229fcfc @ 0x0229fcfc, 0x68 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229cf64(char *p, int a);
extern void func_ov126_022a03dc(char *p, int a);
extern void func_ov095_0229c8e4(char *p, int a);
extern void func_ov002_02208098(char *p, int a);
extern unsigned char data_021fbe40[];

int func_ov126_0229fcfc(char *self)
{
    if (!(((unsigned short *) data_021fbe40)[1] & 0x200)) {
        return 0;
    }
    if (func_ov095_0229cf64(self + 0x19c, 11)) {
        return 0;
    }
    func_ov126_022a03dc(self, 0x118);
    func_ov095_0229c8e4(self + 0x19c, 0x109);
    *(unsigned char *) (self + 0xae) = *(unsigned char *) (self + 0x8d);
    func_ov002_02208098(self, 13);
    return 0;
}
