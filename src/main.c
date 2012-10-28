#include "upan.h"
static void
size_cb(gpointer obj, gpointer user_data)
{
    g_print("here size changed\n");
}

static void
serial_cb(gpointer obj, gpointer user_data)
{
    g_print("serial changed\n");
}


int
main (void)
{
    if(g_thread_supported() == 0)
        g_thread_init(NULL);

    GMainLoop *main = g_main_loop_new(NULL, FALSE);

    g_type_init ();

    MyUdisk *udisk = g_object_new (MY_TYPE_UDISK,
                                   "lock", TRUE,
                                   "serial", 1,
                                   NULL);
    g_signal_connect(udisk, "size-change",G_CALLBACK(size_cb), NULL);
    g_signal_connect(udisk, "notify::serial", G_CALLBACK(serial_cb), NULL);

    GValue value = {0,};
    g_value_init(&value, G_TYPE_INT);
    g_value_set_int(&value, 65);

    g_object_set_property(G_OBJECT(udisk), "size", &value);

    g_object_set_property(G_OBJECT(udisk),"serial", &value);

    g_object_get_property(G_OBJECT(udisk), "size", &value);

    int a = g_value_get_int(&value);

    g_print("%d+++++\n", a);



    my_iusb_write (MY_IUSB (udisk), "I am u-disk!");
    gchar *data = my_iusb_read (MY_IUSB (udisk));

    g_printf ("%s\n\n", data);

    g_printf ("Is udisk a MyIUsb object?\n");
    if (MY_IS_IUSB (udisk))
        g_printf ("Yes!\n");
    else
        g_printf ("No!\n");

    g_printf ("\nIs udisk a MyUdisk object?\n");
    if (MY_IS_UDISK (udisk))
        g_printf ("Yes!\n");
    else
        g_printf ("No!\n");

    g_main_loop_run(main);
    return 0;
}
