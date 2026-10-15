/* func_020663d4 @ 0x020663d4, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020707d0(void *ptr);
extern void *func_020707b8(void *ptr);
extern int func_020a87e0(void *p1, void *p2);
extern void func_02051c08(void *dst, const void *src, unsigned int size);
extern void *func_02065cb0(void *ptr);
extern void func_0205195c(void *ptr);
extern void __register_global_object(void *, void *, void *);
extern void *func_02065c98(void *);

extern unsigned int data_021cd890;
extern unsigned int data_021cd920;
extern unsigned int data_021cd8ac;
extern unsigned int data_021cd92e;

void func_020663d4(unsigned char *self, void *src1, void *arg2, void *arg3, void *stackArg5)
{
    unsigned char local_buf[0x60];

    self[0xf8] = (unsigned char) (*(unsigned int *) src1);
    func_020707d0(local_buf);
    func_020a87e0(local_buf, arg2);
    func_02051c08(local_buf + 0xe, self + 0x44, 0xa);

    if ((data_021cd890 & 1) == 0) {
        func_02065cb0(&data_021cd920);
        __register_global_object((void *) (&data_021cd920), (((void *) func_02065c98)), (void *) (&data_021cd8ac));
        data_021cd890 |= 1;
    }

    func_0205195c(&data_021cd920);
    func_020a87e0(&data_021cd920, arg3);
    func_02051c08(&data_021cd92e, self + 0x58, 0x40);
    func_020a87e0(local_buf, stackArg5);
    func_02051c08(local_buf + 0xe, self + 0xd8, 0x10);
    func_020707b8(local_buf);
}
