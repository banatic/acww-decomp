/* func_ov121_0229c19c @ 0x0229c19c, 0x74 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int size);
extern void func_ov002_0220830c(void *);
extern void func_ov002_02207e40(void *);
extern void func_ov002_02209ccc(void *);
extern void func_ov002_0220ba24(void *);
extern void func_ov002_02209b14(void *);
extern void func_020b9af4(void *);

extern unsigned char data_ov121_0229c3a8[];

void *func_ov121_0229c19c(void)
{
    void *obj;
    char *p, *end;

    obj = func_ov002_02207f80(0x1194);
    if (obj != 0) {
        func_ov002_0220830c(obj);
        *(int *) obj = (unsigned int) data_ov121_0229c3a8;
        func_ov002_02207e40((char *) obj + 0x2d8);
        func_ov002_02209ccc((char *) obj + 0x3a8);
        func_ov002_0220ba24((char *) obj + 0x40c);
        func_ov002_02209b14((char *) obj + 0x528);

        p = (char *) obj + 0x91c;
        end = (char *) obj + 0x98c;
        do {
            func_020b9af4(p);
            p += 0x38;
        } while (p != end);
    }
    return obj;
}
