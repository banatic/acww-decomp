/* func_ov126_0229f930 @ 0x0229f930, 0x38 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02088220(void *record);
extern void func_02051c08(const void *src, void *dst, unsigned int size);
extern void *func_02072d4c(void *ptr);
extern void func_02072e3c(void *a, void *b);

extern unsigned char data_021f3278[];

void func_ov126_0229f930(void *self)
{
    char buffer[20];
    void *handle;

    handle = func_02088220(data_021f3278);
    func_02051c08((char *) self + 0x4248, buffer, 10);
    func_02072e3c(func_02072d4c(handle), buffer);
}
