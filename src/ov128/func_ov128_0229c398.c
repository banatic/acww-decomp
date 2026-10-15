/* func_ov128_0229c398 @ 0x0229c398, 0x70 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b1774(void *);
extern void func_ov127_02299e5c(void *);
extern void func_ov002_0220b290(void *);
extern void func_02070b84(void *);
extern int func_02095904(void);
extern void func_02035834(void *);
extern int func_02002c6c(void *, void *, int, int, int, int);
extern void *data_021c526c;
extern void *data_021fbe94;
extern char data_ov128_0229cd20;

void func_ov128_0229c398(char *obj)
{
    func_020b1774(obj + 0x174);
    func_ov127_02299e5c(obj + 0x4a4);
    func_ov002_0220b290(obj + 0x94);
    func_02070b84(obj + 0x2cdc);
    func_02095904();
    func_02035834((char *) data_021c526c + 0x2f0);
    func_02002c6c(&data_ov128_0229cd20, data_021fbe94, 3, 0, 0x10, 0x10);
}
