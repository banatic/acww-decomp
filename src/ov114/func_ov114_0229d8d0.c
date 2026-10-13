/* func_ov114_0229d8d0 @ 0x0229d8d0, 0x108 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002d50(unsigned char);
extern void func_ov094_0229b0d4(void *);
extern void func_ov114_0229c9dc(void *);
extern void func_ov114_0229c1e4(void *);
extern void func_ov002_0220a580(void *);
extern void func_020a8c1c(void *);

void func_ov114_0229d8d0(unsigned char *obj, unsigned char p1, unsigned char p2, unsigned char p3, unsigned char p4)
{
    *(unsigned short *) (obj + 0x12ac) = 0;
    *(obj + 0x12b1) = p1;
    *(obj + 0x12b2) = p2;
    *(obj + 0x12b3) = p3;
    *(unsigned int *) (obj + 0x12a4) = func_02002d50(p2);
    *(unsigned int *) (obj + 0x12a8) = func_02002d50(p3);
    *(obj + 0x12b7) = p4;
    func_ov094_0229b0d4(obj);
    func_ov114_0229c9dc(obj);
    switch (p4) {
        case 0:
            *(unsigned int *) (obj + 0x1294) = 0x38;
            *(obj + 0x12bd) = 7;
            break;
        case 1:
            *(unsigned int *) (obj + 0x1294) = 0x38;
            *(obj + 0x12bd) = 8;
            break;
        default:
            *(unsigned int *) (obj + 0x1294) = 0x38;
            *(obj + 0x12bd) = 0;
            break;
    }
    func_ov114_0229c1e4(obj);
    *(obj + 0x12bc) = 0x10;
    *(unsigned int *) (obj + 0x1298) = (*(unsigned int *) (obj + 0x1294) - 8) * 0x1b;
    *(unsigned int *) (obj + 0x1280) = 0;
    func_ov002_0220a580(obj + 0x121c);
    *(obj + 0x12af) = 0;
    *(obj + 0x12ae) = *(obj + 0x12af);
    func_020a8c1c(obj + 0x808);
    *(obj + 0x12bb) = 4;
}
