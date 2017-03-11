#include<gtk-2.0/gtk/gtk.h>
#include<glib-2.0/glib.h>
#include</usr/include/gtk-2.0/gdk/gdkkeysyms.h>

#define EVENT_METHOD(i,x) GTK_WIDGET_GET_CLASS(i)->x

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
GtkWidget* LableTool(GtkWidget *MTbox)
{
//	GtkWidget *window1;//标签菜单
//	window1=gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_widget_show(window1);
	//g_signal_connect(G_OBJECT(window1),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	GtkAccelGroup *accel_group;
	accel_group=gtk_accel_group_new();
	GtkWidget* menubar1;
	menubar1=gtk_menu_bar_new();	
//	gtk_widget_show(menubar1);
	//gtk_window_set_default_size(GTK_WINDOW(menubar1),40,300);
//	gtk_container_add(GTK_CONTAINER(window1),menubar1);
	gtk_box_pack_start(GTK_BOX(MTbox),menubar1,FALSE,FALSE,3);
	GtkWidget*menuitem1;
	menuitem1=gtk_menu_item_new_with_mnemonic("文件(_F)");
//	gtk_widget_show(menuitem1);
	gtk_container_add(GTK_CONTAINER(menubar1),menuitem1);
	GtkWidget*menuitem2;
	menuitem2=gtk_menu_item_new_with_mnemonic("编辑(_C)");
//	gtk_widget_show(menuitem2);  
	gtk_container_add(GTK_CONTAINER(menubar1),menuitem2);
	GtkWidget*menuitem1_menu;
	menuitem1_menu=gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem1),menuitem1_menu);
	GtkWidget* open1;
	GtkWidget* save1;
	GtkWidget* exit1;
	GtkWidget* close1;
	open1=gtk_menu_item_new_with_mnemonic("打开");
//	gtk_widget_show(open1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu),open1);
	gtk_widget_add_accelerator(open1,"activate",accel_group,GDK_o,
			(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

	save1=gtk_menu_item_new_with_mnemonic("保存");
//	gtk_widget_show(save1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu),save1);
	gtk_widget_add_accelerator(save1,"activate",accel_group,GDK_s,
			(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

	close1=gtk_menu_item_new_with_mnemonic("退出");
//	gtk_widget_show(close1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu),close1);
	gtk_widget_add_accelerator(close1,"activate",accel_group,GDK_c,
			(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

	exit1 =gtk_menu_item_new_with_mnemonic("关闭");
//	gtk_widget_show(exit1);
	gtk_container_add(GTK_CONTAINER(menuitem1_menu),exit1);
	gtk_widget_add_accelerator(exit1,"activate",accel_group,GDK_x,
			(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
//	gtk_main();
//	menubar1=gtk_menu_bar_new();	
//`	return menubar1;
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
	GtkWidget *MainWin,*MTbox;
	GtkWidget *RulerH,*RulerV,*table,*area;
	gtk_init(&argc,&argv);
	MainWin=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(MainWin),"HAAPY PAINT");
	gtk_window_set_default_size(GTK_WINDOW(MainWin),400,300);
	gtk_window_set_position(GTK_WINDOW(MainWin),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(MainWin),0);
	GtkWidget *Menubox;
	MTbox=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(MainWin),MTbox);
	LableTool(MTbox);
	GtkWidget *PaintMap;
	PaintMap =gtk_button_new_with_label("jjj");
	gtk_box_pack_start(GTK_BOX(MTbox),PaintMap,FALSE,FALSE,0);
	//
	table =gtk_table_new(3,2,FALSE);
	gtk_box_pack_start(GTK_BOX(MTbox),table,TRUE,TRUE,3);
	area=gtk_drawing_area_new();
	gtk_widget_set_size_request(GTK_WIDGET(area),600,400);
	gtk_table_attach(GTK_TABLE(table),area,1,2,1,2,GTK_EXPAND|GTK_FILL,GTK_FILL,0,0);
	gtk_widget_set_events(area,GDK_POINTER_MOTION_MASK|GDK_POINTER_MOTION_HINT_MASK);
	RulerH=gtk_hruler_new();
	gtk_ruler_set_metric(GTK_RULER(RulerH),GTK_PIXELS);
	gtk_ruler_set_range(GTK_RULER(RulerH),7,13,0,20);
	g_signal_connect_swapped(G_OBJECT(area),"motion_notify_event",G_CALLBACK(EVENT_METHOD(RulerH,motion_notify_event)),RulerH);
	gtk_table_attach(GTK_TABLE(table),RulerH,1,2,0,1,GTK_EXPAND|GTK_SHRINK|GTK_FILL,GTK_FILL,0,0);
	RulerV=gtk_vruler_new();
	gtk_ruler_set_metric(GTK_RULER(RulerV),GTK_PIXELS);
	gtk_ruler_set_range(GTK_RULER(RulerV),0,400,10,400);
	g_signal_connect_swapped(G_OBJECT(area),"motion_notify_event",G_CALLBACK(EVENT_METHOD(RulerV,motion_notify_event)),RulerV);
	gtk_table_attach(GTK_TABLE(table),RulerV,0,1,1,2,GTK_FILL,GTK_EXPAND|GTK_SHRINK|GTK_FILL,0,0);
	g_signal_connect(GTK_OBJECT(MainWin),"delete_event",G_CALLBACK(destroy_window),(gpointer)MainWin);
	g_signal_connect(GTK_OBJECT(MainWin),"delete_event",G_CALLBACK(destroy_window),(gpointer)MainWin);
	gtk_widget_show_all(MainWin);
	//LableTool();
	gtk_main();
	return 0;
}
