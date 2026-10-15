/* func_ov143_0229a230 @ 0x0229a230, 0x54 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fc4c(int);
extern void *func_ov002_0220a720(void *, int);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_0206ea84(void *, void *);
extern void func_0206ea28(void);
extern void func_0207a500(void *);
extern void func_ov143_0229a1a4(void *);

extern unsigned char data_021e5a2c[];
extern unsigned char data_021f3b68[];

void func_ov143_0229a230(void *arg0)
{
    func_0206fc4c(1);
    func_ov002_0220a720((char *) arg0 + 0x110, 1);
    func_ov002_02208090(arg0, 2);
    func_ov002_02208098(arg0, 9);
    func_0206ea84((void *) data_021f3b68, *(void **) ((char *) arg0 + 0xa0));
    func_0206ea28();
    func_0207a500((void *) data_021e5a2c);
    func_ov143_0229a1a4(arg0);
}
