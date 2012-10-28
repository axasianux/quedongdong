#include "upan.h"

static void
my_iusb_interface_init (MyIusbInterface *iface);

G_DEFINE_TYPE_WITH_CODE (MyUdisk, my_udisk, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (MY_TYPE_IUSB, my_iusb_interface_init));

#define MYUDISK_GET_PRIVATE(obj) \
    G_TYPE_INSTANCE_GET_PRIVATE((obj), MY_TYPE_UDISK, MyUdiskPrivate)

enum PORPLIST
{
    PROP0,
    PROPLOCK,
    PROPSERIAL,
    PROPSIZE
};

enum SIGNALLIST
{
    SIZECHANGE,
    LASTSIGNAL
};

typedef struct _MyUdiskPrivate MyUdiskPrivate;
struct _MyUdiskPrivate
{
    gboolean lock;
    int serial;
    int size;
};

static guint my_udisk_signal[LASTSIGNAL] = {0,};


static void
my_udisk_set_property(GObject *object, guint p_id,
                     const GValue *value, GParamSpec *param)
{
    MyUdisk *obj = MY_UDISK(object);
    MyUdiskPrivate *m_private = MYUDISK_GET_PRIVATE(obj);

    switch(p_id)
    {
        case PROPLOCK:
            m_private->lock = g_value_get_boolean(value);
            break;

        case PROPSERIAL:
            m_private->serial = g_value_get_int(value);
            g_object_notify(object, "serial");
            break;

        case PROPSIZE:
            m_private->size = g_value_get_int(value);
            g_signal_emit_by_name(obj, "size-change");
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, p_id, param);
            break;
    }
}

static void
my_udisk_get_property(GObject *object, guint p_id,
                      GValue *value, GParamSpec *gparam)
{
    MyUdisk *obj = MY_UDISK(object);
    MyUdiskPrivate *m_private = MYUDISK_GET_PRIVATE(obj);

    switch (p_id)
    {
        case PROPLOCK:
            g_value_set_boolean(value, m_private->lock);
            break;

        case PROPSERIAL:
            g_value_set_int(value, m_private->serial);
            break;

        case PROPSIZE:
            g_value_set_int(value, m_private->size);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, p_id, gparam);
            break;
    }
}

static gchar *
my_udisk_read (MyIusb *iusb)
{
    MyUdisk *udisk = MY_UDISK (iusb);
    return udisk->data->str;
}

static void
my_udisk_write (MyIusb *iusb, const gchar *str)
{
    MyUdisk *udisk = MY_UDISK (iusb);
    g_string_assign (udisk->data, str);
}



static void
my_udisk_class_init (MyUdiskClass *self)
{
    g_type_class_add_private(self, sizeof(MyUdiskPrivate));
    GObjectClass *parent = G_OBJECT_CLASS(self);
    parent->set_property = my_udisk_set_property;
    parent->get_property = my_udisk_get_property;

    GParamSpec *param;
    param = g_param_spec_boolean("lock", "...", "...", TRUE, G_PARAM_READWRITE);
    g_object_class_install_property(parent, PROPLOCK, param);

    param = g_param_spec_int("serial", "...", "...", 0, 1000, 1, G_PARAM_READWRITE);
    g_object_class_install_property(parent, PROPSERIAL, param);

    param = g_param_spec_int("size", "...", "...", 0, 1000, 1, G_PARAM_READWRITE);
    g_object_class_install_property(parent, PROPSIZE, param);


    my_udisk_signal[SIZECHANGE] = g_signal_new("size-change", G_TYPE_FROM_CLASS(self),
                 G_SIGNAL_RUN_LAST, 0,
                 NULL, NULL, g_cclosure_marshal_VOID__VOID,
                 G_TYPE_NONE, 0);

}


static void
my_udisk_init (MyUdisk *self)
{
    self->data = g_string_new (NULL);
    MyUdiskPrivate *m_private = MYUDISK_GET_PRIVATE(self);
    m_private->lock = TRUE;
    m_private->serial = 1000;
    m_private->size = 512;
}

static void
my_iusb_interface_init (MyIusbInterface *iface)
{
    iface->read = my_udisk_read;
    iface->write = my_udisk_write;
}

//MyUdisk *my_udisk_new(void)
//{
//    return g_object_new(MY_TYPE_UDISK, NULL);
//}
