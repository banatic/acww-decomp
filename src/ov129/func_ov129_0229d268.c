/* func_ov129_0229d268 @ 0x0229d268, 0x68 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b1774(void *);
extern void func_ov127_02299e5c(void *);
extern void func_ov002_0220af74(void *);
extern int func_02095904(void);
extern void func_02035834(void *);
extern int func_02002c6c(void *, int, int, int, int, int);

extern void *data_021c526c;
extern int data_ov129_0229dc98;
extern int data_021fbe94;

void func_ov129_0229d268(void *obj)
{
    func_020b1774((char *) obj + 0x404);
    func_ov127_02299e5c((char *) obj + 0x734);
    func_ov002_0220af74((char *) obj + 0x1d4);
    func_02095904();
    func_02035834((char *) data_021c526c + 0x2f0);
    func_02002c6c(&data_ov129_0229dc98, data_021fbe94, 3, 0, 0x10, 0x10);
}
