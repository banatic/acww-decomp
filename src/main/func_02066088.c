/* func_02066088 @ 0x02066088, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02066088 {
    char data[32];
} UnkStruct_02066088;

extern void *func_0209529c(UnkStruct_02066088 *this);
extern void func_0209525c(UnkStruct_02066088 *this, int value);
extern int func_0209526c(UnkStruct_02066088 *this);
extern void func_02066650(char *a);
extern void func_020666b0(char *a, int val);
extern void func_020666d0(char *a, UnkStruct_02066088 *this);
extern void func_02065eac(char *a, int val);
extern void func_020663d4(char *a, int *e, int b, int c, int d);

void func_02066088(char *a, int b, int c, int d, int e, unsigned char *fptr, unsigned char *gptr, int h)
{
    UnkStruct_02066088 local;
    func_0209529c(&local);
    func_0209525c(&local, h);
    func_02066650(a);
    a[0xf9] = *gptr;
    a[0xfb] = *fptr;
    func_020666b0(a + 0x24, 4);
    func_020666d0(a + 4, &local);
    if (e < 0) {
        func_020666b0(a + 4, 6);
        e = 0;
    }
    func_02065eac(a, 2);
    func_020663d4(a, &e, b, c, d);
    func_0209526c(&local);
}
