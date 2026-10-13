/* func_ov130_0229a0a4 @ 0x0229a0a4, 0x80 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov130_0229a848[];
extern unsigned char data_ov130_0229a818[];
extern unsigned char data_ov130_0229a828[];
extern unsigned char data_ov130_0229a838[];

extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);

int func_ov130_0229a0a4(int param0, int param1)
{
    int r5;
    int r4;
    int r6;
    int r0;
    int r1;

    r5 = param0;
    r4 = param1;
    if (r4 == 0) {
        return 0;
    }
    r6 = *(unsigned char *) (r5 + 5);
    r0 = r4;
    if (func_ov002_022088cc(r0) != 0) {
        r1 = *(unsigned char *) (r5 + 5);
        r0 = data_ov130_0229a848[r1];
        *(unsigned char *) (r5 + 5) = r0;
        goto label_0229a0da;
    }
    r0 = r4;
    if (func_ov002_022088bc(r0) != 0) {
        r1 = *(unsigned char *) (r5 + 5);
        r0 = data_ov130_0229a818[r1];
        *(unsigned char *) (r5 + 5) = r0;
    }
label_0229a0da:
    r0 = r4;
    if (func_ov002_022088ac(r0) != 0) {
        r1 = *(unsigned char *) (r5 + 5);
        r0 = data_ov130_0229a828[r1];
        *(unsigned char *) (r5 + 5) = r0;
        goto label_0229a100;
    }
    r0 = r4;
    if (func_ov002_0220889c(r0) != 0) {
        r1 = *(unsigned char *) (r5 + 5);
        r0 = data_ov130_0229a838[r1];
        *(unsigned char *) (r5 + 5) = r0;
    }
label_0229a100:
    r0 = *(unsigned char *) (r5 + 5);
    if (r6 == r0) {
        return 0;
    }
    return 1;
}
