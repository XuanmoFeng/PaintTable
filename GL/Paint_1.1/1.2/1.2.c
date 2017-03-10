#include<gtk-2.0/gtk/gtk.h>
#include<glib-2.0/glib.h>
#include</usr/include/gtk-2.0/gdk/gdkkeysyms.h>
GtkWidget *coloresldlg =NULL;
GtkWidget *drawingarea =NULL;
GdkColor color;
void CreateDir()
{//建文件目录
	GtkWidget*dialog;
	gchar *filename;
	gint result;
	dialog=gtk_file_chooser_dialog_new("创建新目录",NULL,
			GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER,
			GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
			GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	result=gtk_dialog_run(GTK_DIALOG(dialog));
	if(result==GTK_RESPONSE_OK)
	{
		filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		g_print("已经创建一个新目录:%s\n",filename);
	}
	gtk_widget_destroy(dialog);
}
GtkWidget* LableTool()
{
	GtkWidget *window1;//标签菜单
	window1=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(window1);
	g_signal_connect(G_OBJECT(window1),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	GtkAccelGroup *accel_group;
	accel_group=gtk_accel_group_new();
	GtkWidget* menubar1;
	menubar1=gtk_menu_bar_new();	
	gtk_widget_show(menubar1);
	gtk_container_add(GTK_CONTAINER(window1),menubar1);
	GtkWidget*menuitem1;
	menuitem1=gtk_menu_item_new_with_mnemonic("文件(_F)");
	gtk_widget_show(menuitem1);
	gtk_container_add(GTK_CONTAINER(menubar1),menuitem1);
	GtkWidget*menuitem2;
	menuitem2=gtk_menu_item_new_with_mnemonic("编辑(_C)");
	gtk_widget_show(menuitem2);  
	gtk_container_add(GTK_CONTAINER(menubar1),menuitem2);
	GtkWidget*menuitem1_menu;
	menuitem1_menu=gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem1),menuitem1_menu);
	GtkWidget* open1;
	GtkWidget* save1;
	GtkWidget* exit1;
	GtkWidget* close1;
	open1=gtk_menu_item_new_with_mnemonic("打开");
	gtk_widget_show(open1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu),open1);
	gtk_widget_add_accelerator(open1,"activate",accel_group,GDK_o,
			(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

	save1=gtk_menu_item_new_with_mnemonic("保存");
	gtk_widget_show(save1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu),save1);
	gtk_widget_add_accelerator(save1,"activate",accel_group,GDK_s,
			(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

	close1=gtk_menu_item_new_with_mnemonic("退出");
	gtk_widget_show(close1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu),close1);
	gtk_widget_add_accelerator(close1,"activate",accel_group,GDK_c,
			(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

	exit1 =gtk_menu_item_new_with_mnemonic("关闭");
	gtk_widget_show(exit1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu),exit1);
	gtk_widget_add_accelerator(exit1,"activate",accel_group,GDK_x,
			(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_main();
	return window1;
}
/*GtkWidget* creat_menu(void)
  {
  GtkWidget*menu;
  GtkWidget*copy;
  GtkWidget*cut;
  GtkWidget*delte;
  GtkAccelGroup*accel_group;
  accel_group =gtk_accel_group_new;
  menu =gtk_menu_new;
  c
  }*/
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
GtkWidget*ColorTest()
{
	GtkWidget *window;
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
}
gint main(int argc,char *argv[])
{
	gtk_init(&argc,&argv);
	LableTool();
	return 0;
}
