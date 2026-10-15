/* func_ov118_0229bc7c @ 0x0229bc7c, 0x50 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_0208e95c(char *, int);
extern void func_ov118_0229b8b0(char *);
extern int func_020e895c(int *, int, int);
extern void func_ov118_0229ac44(char *, int);

void func_ov118_0229bc7c(char *param)
{
    if (data_021fbdd8 == 0) {
        func_0208e95c(param + 0x678, 3);
        func_ov118_0229b8b0(param);
    }
    {
        int local;
        local = *(unsigned char *) (param + 0xa4);
        func_020e895c(&local, data_021f6c54 - 0x54, 8);
        func_ov118_0229ac44(param, local);
    }
}
