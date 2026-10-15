/* func_ov136_0229d3d4 @ 0x0229d3d4, 0x44 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int size);
extern void *func_ov002_0220830c(void *obj);
extern void *func_ov002_02209ccc(void *obj);
extern void *func_ov002_0220b008(void *obj);
extern void *func_ov134_0229bed4(void *obj);
extern unsigned char data_ov136_0229d510;

void *func_ov136_0229d3d4(void)
{
    void *obj;
    obj = func_ov002_02207f80(0x2b78);
    if (obj) {
        func_ov002_0220830c(obj);
        *(void **) obj = &data_ov136_0229d510;
        func_ov002_02209ccc((char *) obj + 0x94);
        func_ov002_0220b008((char *) obj + 0xf8);
        func_ov134_0229bed4((char *) obj + 0x2c4);
    }
    return obj;
}
