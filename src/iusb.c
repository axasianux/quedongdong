#include "iusb.h"

G_DEFINE_INTERFACE(MyIusb, my_iusb, G_TYPE_INVALID);

static void
my_iusb_default_init(MyIusbInterface *iface)
{

}

gchar *my_iusb_read(MyIusb *self)
{
    g_return_if_fail(MY_IUSB(self));
    MY_IUSB_GET_INTERFACE(self)->read(self);
}

void
my_iusb_write(MyIusb *self, const char *str)
{
    g_return_if_fail(MY_IUSB(self));
    MY_IUSB_GET_INTERFACE(self)->write(self, str);
}
