/* func_ov052_022613a8 @ 0x022613a8, 0x44 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} UnkStruct_022613a8;
extern UnkStruct_022613a8 *func_02095794(int);
extern int func_02014868(void *);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern void func_ov052_02261908(void *, int);

int func_ov052_022613a8(char *self)
{
    volatile int a, b, c;
    UnkStruct_022613a8 *p = func_02095794(4);
    a = p->x;
    b = p->y;
    c = p->z;
    if (func_02014868(self + 0x618) == 0) {
        func_020b6098(func_020b5e10(), 0);
        func_ov052_02261908(self, 7);
    }
    return 1;
}
