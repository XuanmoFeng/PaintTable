#include<gtk-2.0/gtk/gtk.h>
#include<glib-2.0/glib.h>
#include</usr/include/gtk-2.0/gdk/gdkkeysyms.h>



#define EVENT_METHOD(i,x) GTK_WIDGET_GET_CLASS(i)->x

GdkPixbuf *create_pixbuf(const gchar *filename);
void color_changed_cb(GtkWidget *widgt,GtkColorSelection *colorsel);
GtkWidget*ColorTest();

GtkWidget* ToolBar(GtkWidget*_toolsbar);//toolbar
GtkWidget* CreatMenu(GtkWidget *MTbox);//MenuBar
