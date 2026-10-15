/* func_02066344 @ 0x02066344, 0x8e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003780(void *);
extern void func_02003728(void *, int);
extern int func_02003750(void *);
extern void *func_0209529c(void *);
extern void func_0209525c(void *, int);
extern int func_0209526c(void *);
extern void func_02066650(void *);
extern void func_020666e4(void *, void *);
extern void func_020666d0(void *, void *);
extern void func_020666b0(void *, int);
extern void func_02065eac(void *, int);
extern void func_020663d4(void *, int *, int, int, int);

void func_02066344(char *obj, int arg1, int arg2, int arg3, int arg5, unsigned char *arg6, int arg7, int arg8)
{
    unsigned char local0[0x10];
    unsigned char local1[0x20];

    func_02003780(local0);
    func_0209529c(local1);
    func_02003728(local0, arg7);
    func_0209525c(local1, arg8);
    func_02066650(obj);

    obj[0xf9] = *arg6;
    obj[0xfb] = 0;

    func_020666e4(obj + 0x24, local0);
    func_020666d0(obj + 4, local1);

    if (arg5 < 0) {
        func_020666b0(obj + 4, 5);
        arg5 = 0;
    }

    func_02065eac(obj, 2);
    func_020663d4(obj, &arg5, arg1, arg2, arg3);

    func_0209526c(local1);
    func_02003750(local0);
}
