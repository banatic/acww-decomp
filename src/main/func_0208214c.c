/* func_0208214c @ 0x0208214c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208214c;
struct UnkStruct_0208214c_2 {
    struct UnkStruct_0208214c *data;
};
extern struct UnkStruct_0208214c data_020e1934;
extern void *func_020a887c(struct UnkStruct_0208214c_2 *);

struct UnkStruct_0208214c_2 *func_0208214c(struct UnkStruct_0208214c_2 *obj)
{
    obj->data = &data_020e1934;
    func_020a887c(obj);
    return obj;
}
