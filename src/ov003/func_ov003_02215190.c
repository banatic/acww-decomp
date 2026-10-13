/* func_ov003_02215190 @ 0x02215190, 0xa4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern unsigned char func_0203cc38(unsigned int);
extern int func_02073908(void *, unsigned int);
extern unsigned char *func_020604f8(unsigned char *);
extern void func_02079798(unsigned char *);
extern void func_0208b500(void);
extern void func_0208d09c(void);
extern void func_020109a0(unsigned char *, int, volatile long long);
extern void func_0205eae0(unsigned char *, int, int, int);
extern void func_ov003_0221523c(unsigned char *, unsigned char);
void func_ov003_02215190(unsigned char *self, unsigned char *param)
{
    typedef struct {
        unsigned short field_0;
        unsigned char field_2;
        signed char field_3;
        unsigned char field_4;
        unsigned char field_5;
    } Block;
    unsigned char c;
    signed char t;
    Block *block;
    c = param[0xc];
    block = (Block *) (self + 0x7d4);
    block->field_4 = c;
    block->field_0 = 0x39;
    block->field_5 = func_0203cc38(0x39);
    if (c == 0) {
        if (func_02073908(data_020ccf94, *((unsigned int *) (self + 0x800))) != 0) {
            t = *((signed char *) (func_020604f8(self + 0x5c8) + 0x7e));
            block->field_3 = t;
            if (t < 0x38) {
                func_02079798(self + 0x5c);
                func_0208b500();
                func_0208d09c();
            }
        }
        block->field_2 = 0;
        func_020109a0(self, 0x59, 3);
        func_0205eae0(self + 0x5a0, 0x1c, 3, 1);
    } else {
        block->field_2 = 2;
        block->field_0 = 0x3a;
        *((unsigned int *) (self + 0x81c)) = 8;
    }
    func_ov003_0221523c(self + 0x8f0, c);
}
