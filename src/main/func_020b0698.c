/* func_020b0698 @ 0x020b0698, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021ebcc8;
extern int func_020b65ac(int);
extern int func_020b0730(int);
extern void func_020b0a3c(unsigned char *);
extern int func_020b0a20(unsigned char *);
extern int func_020b0860(unsigned char *);

typedef struct UnkStruct_020b0698 {
    unsigned char pad_00[8];
    unsigned char a : 2;
    unsigned char f : 6;
} UnkStruct_020b0698;

void func_020b0698(unsigned char *self)
{
    unsigned int i;
    int r;
    unsigned char *p;
    int k = func_020b65ac(((UnkStruct_020b0698 *) &data_021ebcc8)->f);
    int flag = 0;
    for (i = 0; i < 3; i++) {
        if (k == 0) {
            if (func_020b0730(i)) {
                func_020b0a3c(self + i * 6);
            }
        } else {
            p = self + i * 6;
            r = func_020b0a20(p);
            if (r != 0) {
                r = func_020b0860(p);
                if (((p[5] != 0) ? 1 : *(volatile int *) &flag) == 0) {
                    if (r != 0) {
                        func_020b0a3c(p);
                    }
                } else {
                    if (r >= 3 || r < 0) {
                        if (func_020b0730(i)) {
                            func_020b0a3c(p);
                        }
                    } else {
                        p[4] = (char) r;
                    }
                }
            }
        }
    }
}
