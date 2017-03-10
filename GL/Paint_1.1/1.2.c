#include"1_2.h"
GtkWidget *coloresldlg =NULL;
GtkWidget *drawingarea =NULL;
GdkColor color;
void color_changed_cb(GtkWidget *widgt,GtkColorSelection *colorsel)
{
	GdkColor ncolor;
	gtk_color_selection_get_current_color(colorsel,&ncolor);
	gtk_widget_modify_bg(drawingarea,GTK_STATE_NORMAL,&ncolor);
	
}
gint area_event(GtkWidget *widgt,
				GdkEvent *event,
				gpointer client_data)
{
	gint handled = FALSE;
	gint response;
	GtkColorSelection *colorsel;
	if(event->type ==GDK_BUTTON_PRESS)
	{
		handled=TRUE;
		if(coloresldlg==NULL)
		{
			coloresldlg =gtk_color_selection_dialog_new("颜色选择对话框");
		}
		colorsel =GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG
		(coloresldlg)->colorsel);
		gtk_color_selection_set_previous_color(colorsel,&color);
		gtk_color_selection_set_current_color(colorsel,&color);
		gtk_color_selection_set_has_palette(colorsel,TRUE);
		g_signal_connect(G_OBJECT(colorsel),"color_changed",G_CALLBACK(color_changed_cb),(gpointer)colorsel);
		response=	gtk_dialog_run(GTK_DIALOG(coloresldlg));
		if(response ==GTK_RESPONSE_OK)
		{
			gtk_color_selection_set_current_color(colorsel,&color);
		}
		else
		{
			gtk_widget_modify_bg(drawingarea,GTK_STATE_NORMAL,&color);	
		}
		gtk_widget_hide(coloresldlg);
	}
	return handled;
}
gint destroy_window(GtkWidget *wiget,
			GdkEvent *event,
			gpointer data)
{
	gtk_main_quit();
	return TRUE;
}
gint main(int argc,char *argv[])
{
	GtkWidget *window;
	gtk_init(&argc,&argv);
	window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"颜色选择测试");
	gtk_window_set_policy(GTK_WINDOW(window),TRUE,TRUE,TRUE);
	g_signal_connect(GTK_OBJECT(window),"delete_event",G_CALLBACK(destroy_window),(gpointer)window);
	drawingarea=gtk_drawing_area_new();
	color.red =0;
	color.blue=65535;
	color.green=0;
	gtk_widget_modify_bg(drawingarea,GTK_STATE_NORMAL,&color);
	gtk_widget_set_size_request(GTK_WIDGET(drawingarea),200,200);
	gtk_widget_set_events(drawingarea,GDK_BUTTON_PRESS_MASK);
	g_signal_connect(GTK_OBJECT(drawingarea),"event",GTK_SIGNAL_FUNC(area_event),(gpointer)drawingarea);
	gtk_container_add(GTK_CONTAINER(window),drawingarea);
	gtk_widget_show(drawingarea);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
