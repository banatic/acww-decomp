/* func_020baa28 @ 0x020baa28, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_020e54a8;
extern int data_021f6cd8;
extern unsigned char data_021f75b0;
extern unsigned char data_021fa6b4;
extern unsigned char data_021f8b48;
extern unsigned char data_021f6d2c;

void func_020bb8e0(void *p);
int func_020befa0(void *p);
int func_020ba540(int x);
void func_020bc4f8(void *p);
int func_0205c024(void *a, int b, void *c, void *d);
int func_020bb89c(int x);
void func_020bbee0(void *p);

void func_020bad44(void);
void func_020bab04(void);
void func_020baad8(void);

extern void func_01ffceb8(void);

int func_020baa28(void *param)
{
    int r4 = 0;
    int r1 = 0;
    int cond = (data_020e54a8 == 0);
    if (cond != 0) {
        r1 = 1;
    }
    data_021f6cd8 = r1;

    func_020bb8e0(&data_021f75b0);

    if (data_021f6cd8 != 0) {
        if (func_020befa0(&data_021fa6b4) != 0 && func_020ba540(0) != 0) {
            func_020bc4f8(&data_021f8b48);
            r4 = func_0205c024(&data_021f6d2c, (unsigned int) func_01ffceb8, (void *) func_020bad44, (void *) func_020bab04);
        }
    } else {
        if (func_020bb89c(0) != 0) {
            r4 = func_0205c024(&data_021f6d2c, 0, 0, (void *) func_020baad8);
        }
    }

    if (r4 != 0) {
        func_020bbee0((void *) ((unsigned char *) param + 0x50));
    }

    return r4;
}
