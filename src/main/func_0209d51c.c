/* func_0209d51c @ 0x0209d51c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O3,s
 */

extern void func_0209d854(int arg);
extern int func_020b65c4(void);
extern int func_020b65b8(void);
extern void func_0209d57c(int arg1, int arg2);

extern unsigned char data_020e54a8;

typedef struct {
    unsigned char low;
    unsigned char high;
} Pair_020d1ad8;
extern Pair_020d1ad8 data_020d1ad8[];

extern unsigned char data_021dc6e8[];

static __inline int check_flag_0209d51c(void)
{
    return data_020e54a8 == 1;
}

void func_0209d51c(void)
{
    int flag;
    int a;
    int b;
    unsigned int i;
    unsigned int j;

    func_0209d854((unsigned int) data_021dc6e8);
    flag = check_flag_0209d51c();
    if (flag != 0) {
        a = func_020b65c4();
        b = func_020b65b8();
        i = 0;
        j = i;
        do {
            if (a == data_020d1ad8[i].high && b == data_020d1ad8[i].low) {
                func_0209d57c(b, j);
            }
            i++;
        } while (i < 2);
    }
}
