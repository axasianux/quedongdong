#ifndef _IUSB_H_
#define _IUSB_H_
#include <glib-object.h>

#define MY_TYPE_IUSB    (my_iusb_get_type())
#define MY_IUSB(obj)    (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_IUSB, MyIusb))
#define MY_IS_IUSB(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MY_TYPE_IUSB))
#define MY_IUSB_GET_INTERFACE(obj)  (\
    G_TYPE_INSTANCE_GET_INTERFACE((obj), MY_TYPE_IUSB, MyIusbInterface))

typedef struct _MyIusb MyIusb;
typedef struct _MyIusbInterface MyIusbInterface;

struct _MyIusbInterface
{
    GTypeInterface parent_interface;
    gchar *(*read)(MyIusb *self);
    void (*write)(MyIusb *self, const char *str);
};

GType my_iusb_get_type(void);

char *my_iusb_read(MyIusb *self);
void my_iusb_write(MyIusb *self, const char *str);






#endif
