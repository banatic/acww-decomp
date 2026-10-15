/* func_0203f5e4 @ 0x0203f5e4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x100];
    unsigned short marker;
} UnkStruct_0203f5e4;

extern int func_020984e8(void);
extern int func_0209895c(int);
extern int func_02066830(char *, UnkStruct_0203f5e4 *);
extern int func_0209985c(int);
extern void func_02066560(char *, int);
extern void func_02066478(char *);
extern int func_02097a74(char *, int, int);
extern void func_02098930(int, int);
extern void func_02066688(char *);
extern void func_02066694(char *);

int func_0203f5e4(UnkStruct_0203f5e4 *arg)
{
    char buf[0x100];
    int r4;
    int r6;

    func_02066694(buf);
    r4 = func_020984e8();
    if (arg->marker != func_0209895c((int) r4)) {
        func_02066830(buf, arg);
        r6 = func_0209985c(r4);
        func_02066560(buf, r6);
        func_02066478(buf);
        if (func_02097a74(buf, r6, 0) != 0) {
            func_02098930(r4, arg->marker);
            func_02066688(buf);
            return 1;
        }
    }
    func_02066688(buf);
    return 0;
}
