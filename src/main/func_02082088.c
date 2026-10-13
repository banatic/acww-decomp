/* func_02082088 @ 0x02082088, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a887c(void *a, void *b);

extern unsigned char data_020e194c[];

void *func_02082088(void *ptr)
{
    *(void **) ptr = (void *) data_020e194c;
    func_020a887c(ptr, (void *) data_020e194c);
    return ptr;
}
