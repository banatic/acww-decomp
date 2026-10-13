/* func_ov112_022a04b8 @ 0x022a04b8, 0x64 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov095_0229cce0(void *);
extern int func_ov095_0229c54c(void *, unsigned char, unsigned char);
extern int func_ov095_0229c448(void *, int, int);
extern void *func_ov112_022a03ac(void *, int);
extern void func_ov095_0229c8e4(void *, int);
extern void func_ov095_0229bf3c(void *);

void *func_ov112_022a04b8(void *self)
{
    int id;
    int tmp;
    void *result;

    func_ov095_0229cce0((char *) self + 0x384);
    id = func_ov095_0229c54c((char *) self + 0x384, data_021f6c58, data_021f6c54);
    if (id == -1) {
        return 0;
    }
    tmp = func_ov095_0229c448((char *) self + 0x384, id, 9);
    result = func_ov112_022a03ac(self, tmp);
    func_ov095_0229c8e4((char *) self + 0x384, id);
    func_ov095_0229bf3c((char *) self + 0x384);
    return result;
}
