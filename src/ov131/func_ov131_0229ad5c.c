/* func_ov131_0229ad5c @ 0x0229ad5c, 0xb0 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov130_02299ddc(void *p);
extern int func_ov130_02299dd8(void *p);
extern int func_ov130_02299dd4(void *p);
extern int func_020984e8(void);
extern int func_020992fc(int argument0);
extern int func_0206fca4(void);
extern void func_020983ec(int a, int b);
extern int func_02099734(int a);
extern void func_02098a24(int a, int b, int c);
extern void func_02060d24(int a, int b);
extern unsigned char data_021ebcd4[];

void func_ov131_0229ad5c(void *obj)
{
    int r4;
    int r5;
    int r6;
    int r7;
    int local0;
    int local4;
    r4 = func_ov130_02299ddc(((char *) obj) + 0x2c4);
    local4 = func_ov130_02299dd8(((char *) obj) + 0x2c4);
    r6 = func_ov130_02299dd4(((char *) obj) + 0x2c4);
    r7 = func_020984e8();
    local0 = func_020992fc(r7);
    r5 = func_0206fca4();
    switch (r5) {
        case 0x36:
            func_020983ec(local0, local4 - r4);
            break;

        case 0x37:

        default:
            func_02098a24(func_02099734(r7), -r4, 1);
            break;

        case 0x38:

        case 0x39:

        case 0x3a:
            break;
    }

    if (r5 == 0x34) {
        goto L34;
    }
    if (r5 == 0x35) {
        goto L35;
    }
    if (r5 == 0x36) {
        goto L36;
    }
    goto Ldone;
Ldone:
    return;

L34:
    func_02060d24((unsigned int) data_021ebcd4, r6 - r4);

    goto Ldone;
L35:
    func_020983ec(local0, r6 + r4);

    goto Ldone;
L36:
    func_02098a24(func_02099734(r7), r4, 1);

    goto Ldone;
}
