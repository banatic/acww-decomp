/* func_0209f794 @ 0x0209f794, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    unsigned char pad[2];
    unsigned short flags;
} data_021fbe40;

extern unsigned char data_021c75b8;
extern void *data_020ccf94;

extern int func_020b65c4(void);
extern int func_0203e31c(void);
extern int func_0203e340(void);
extern int func_0203ec98(void);
extern int func_02073d90(void *);
extern int func_02073918(void *, int);
extern void func_020390b4(void);
extern int func_0203e228(void);
extern void func_0209f820(int, int);

void func_0209f794(int arg)
{
    unsigned int flag;
    void *ptr;

    if ((data_021fbe40.flags & 8) == 0) {
        return;
    }
    if (func_020b65c4() == 45) {
        return;
    }
    if (func_0203e31c() != 0) {
        return;
    }
    if (func_0203e340() != 0) {
        return;
    }
    flag = (data_021c75b8 == 2);
    if (flag == 0) {
        return;
    }
    if (func_0203ec98() != 0) {
        return;
    }
    ptr = data_020ccf94;
    if (func_02073d90(ptr) != 0) {
        if (func_02073918(ptr, 0) == 0) {
            func_020390b4();
            return;
        }
    }
    if (func_0203e228() != 0) {
        func_0209f820(arg, 1);
    }
    return;
}
