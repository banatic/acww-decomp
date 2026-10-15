/* func_ov125_022a09a4 @ 0x022a09a4, 0x60 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *obj);
extern void *func_ov124_0229f460(void *obj);
extern void *func_ov002_02209b14(void *obj);
extern void *func_ov002_02207e40(void *obj);
extern void *func_ov002_02209ccc(void *obj);
extern void *func_ov002_0220b008(void *obj);
extern char data_ov125_022a0ab8;

void *func_ov125_022a09a4(void)
{
    void *obj = func_ov002_02207f80(0x880);
    if (obj) {
        func_ov002_0220830c(obj);
        *(void **) obj = (void *) &data_ov125_022a0ab8;
        func_ov124_0229f460((char *) obj + 0x94);
        func_ov002_02209b14((char *) obj + 0x180);
        func_ov002_02207e40((char *) obj + 0x574);
        func_ov002_02209ccc((char *) obj + 0x644);
        func_ov002_0220b008((char *) obj + 0x6a8);
    }
    return obj;
}
