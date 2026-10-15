/* func_ov141_0229ae80 @ 0x0229ae80, 0x54 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *ptr);
extern void *func_ov139_02299b54(void *ptr);
extern void *func_ov002_02209ccc(void *ptr);
extern void *func_ov002_0220b008(void *ptr);
extern void *func_020b9cfc(void *ptr);
extern char data_ov141_0229af48;

void *func_ov141_0229ae80(void)
{
    void *p;

    p = func_ov002_02207f80(0x1A90);
    if (p != 0) {
        func_ov002_0220830c(p);
        *(void **) p = &data_ov141_0229af48;
        func_ov139_02299b54((char *) p + 0x94);
        func_ov002_02209ccc((char *) p + 0xA38);
        func_ov002_0220b008((char *) p + 0xA9C);
        func_020b9cfc((char *) p + 0xC68);
    }
    return p;
}
