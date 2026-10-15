/* func_ov094_0229b000 @ 0x0229b000, 0x3c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b104(void *p);
extern void *func_020b9af4(void *p);
extern int data_ov094_0229bf90;

void *func_ov094_0229b000(void *obj)
{
    char *p;
    char *end;

    *(int *) obj = (int) &data_ov094_0229bf90;
    func_ov094_0229b104((char *) obj + 0x184);
    p = (char *) obj + 0x98c;
    end = (char *) obj + 0xa34;
    do {
        func_020b9af4(p);
        p += 0x38;
    } while (p != end);

    return obj;
}
