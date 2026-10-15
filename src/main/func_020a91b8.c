/* func_020a91b8 @ 0x020a91b8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3dc4;
extern void *func_020a9260(void *obj);
extern void func_020edb3c(void *obj);

void *func_020a91b8(void *obj)
{
    *(void **) obj = &data_020e3dc4;
    func_020a9260(obj);
    func_020edb3c(obj);
    return obj;
}
