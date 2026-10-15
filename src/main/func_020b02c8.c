/* func_020b02c8 @ 0x020b02c8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b027c(int);
extern int func_0211dc78(int, void *);
extern void func_020b025c(int);
extern void *data_021f4ad8;
extern void *data_021f4ad4;

void func_020b02c8(void)
{
    if (func_020b027c(1)) {
        func_0211dc78(0, data_021f4ad8);
        func_0211dc78(1, data_021f4ad4);
        func_020b025c(1);
    }
}
