/* func_0200cc44 @ 0x0200cc44, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073908(int, int);
extern void func_0200d0b0(int);
extern void func_0200ce2c(int);
extern void func_0200cdc8(int);
extern int func_0201100c(int);
extern void func_02010d64(int);
extern int func_02010ca4(int);
extern int func_0200cce8(int, short *);
extern int func_0200cf50(int);
extern int func_02010ff4(int);
extern void func_0200ef1c(int);
extern void func_0200cccc(int, char *);

void func_0200cc44(int r0)
{
    int r4 = r0;
    short local;
    char local2;

    if (func_02073908(data_020ccf94, *(int *) (r4 + 0x800)) != 0) {
        local = *(short *) (r4 + 0x94);
        func_0200d0b0(r4);
        func_0200ce2c(r4);
        func_0200cdc8(r4);
        func_0201100c(r4);
        func_02010d64(r4);
        func_02010ca4(r4);
        func_0200cce8(r4, &local);
    } else {
        local2 = func_0200cf50(r4);
        func_0200ce2c(r4);
        func_0200cdc8(r4);
        func_02010ff4(r4);
        func_0200ef1c(r4);
        func_0200cccc(r4, &local2);
    }
}
