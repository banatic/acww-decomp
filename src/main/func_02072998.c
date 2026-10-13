/* func_02072998 @ 0x02072998, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e98b4(int);
extern void func_020e9898(int);
extern void func_020721dc(void);
extern void func_020721c4(int);
extern void func_02072994(int);
extern int func_02072da0(void);
extern void func_020721b0(int, int);
extern int func_02072260(void);
extern int func_02072d4c(void);
extern int func_02072ee8(int);
extern int func_02095040(int);
extern void func_020642d0(int, int);
extern void func_02072268(int, int, int);
extern void func_020950cc(int, unsigned short);
extern unsigned short data_020d1860;

extern unsigned char data_021dc7aa[];

void func_02072998(int param)
{
    int result;
    int r6;
    result = func_020e98b4(0x200);
    if (result == 0) {
        return;
    }
    if (result != 0) {
        func_020721dc();
    }
    func_020721c4(result);
    func_02072994(param);
    func_020721b0(result, func_02072da0());
    r6 = func_02072260();
    func_02072994(param);
    func_02072268(r6, func_02072d4c(), 0x10);
    func_02072994(param);
    func_020642d0(func_02095040(func_02072ee8(func_02072d4c())), (unsigned int) data_021dc7aa);
    func_02072994(param);
    func_020950cc(func_02072ee8(func_02072d4c()), data_020d1860);
    func_020e9898(result);
}
