/* func_02023ddc @ 0x02023ddc, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} Pair;

extern unsigned int func_0202d9c4(void *);
extern int func_0209bc40(unsigned char *);
extern int func_02099fe8(void);
extern void func_0209a088(void *, int, int);
extern void *func_020984e8(void);
extern void *func_020996ac(void *);
extern int OSi_DoUnlockByWord__main_0203cd2c(void *, void *, int, int);
extern int func_020154b4(void *, void *, int, int, int);
extern void func_0202dbf0(void *, Pair);
extern void func_0202dac0(void *);
extern const Pair data_020d9100;

void func_02023ddc(void *obj)
{
    int st;

    switch (func_0209bc40((unsigned char *) func_0202d9c4(obj))) {
        case 0xe:
        case 0x10:
            st = func_02099fe8();
            if (st >= 0) {
                func_0209a088((char *) obj + 0x19c, 0, st);
                OSi_DoUnlockByWord__main_0203cd2c(func_020996ac(func_020984e8()), (char *) obj + 0x19c, 0, 1);
            }
            func_020154b4(obj, (char *) obj + 0x19c, 0, 5, 0);
            func_0202dbf0(obj, data_020d9100);
            break;
        case 0x11:
            func_0202dac0(obj);
            break;
    }
}
