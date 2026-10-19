/* func_ov118_0229bd14 @ 0x0229bd14, 0x90 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *p, int flag);
extern void func_ov118_0229b868(void *p);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov118_0229ab64(void *p);
extern void func_0200467c(int cmd);
extern int func_ov118_0229aca0(void *p);
extern void func_ov002_0220a574(void *p);
extern int func_ov118_0229b0e8(void *p);
extern void func_ov118_0229a474(void *p, int param);
extern int func_ov118_0229b310(void *p);

void func_ov118_0229bd14(void *p)
{
    unsigned int flag;

    if (func_ov002_02208054(p, 1) != 0) {
        func_ov118_0229b868(p);
        return;
    }
    flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (flag > 0) {
        if (func_ov118_0229ab64(p) != 0) {
            func_0200467c(0x36);
            return;
        }
        if (func_ov118_0229aca0(p) != 0) {
            func_ov002_0220a574((char *) p + 0x678);
            return;
        }
        if (func_ov118_0229b0e8(p) != 0) {
            func_ov118_0229a474(p, 0x38);
            return;
        }
        if (func_ov118_0229b310(p) != 0) {
            func_ov118_0229a474(p, 0x37);
            return;
        }
    }
}
