#include<gtk/gtk.h>
gint delete_event(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	g_print("程序已退出\n");
	return TRUE;
};
void destroy(GtkWidget *wiget,
			gpointer data)
{
	gtk_main_quit();

}
void enter(int argc,char *argv[])
{
	GtkWidget *window;//声明一个窗口
	GtkWidget *button;	//声明一个按钮
	gint tmp_pos;

	GtkWidget *entry;//声明一个文本框
	entry=gtk_entry_new();//创建文本输入框
	gtk_
	void gtk_entry_set_text
	gtk_init(&argc,&argv);
	window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window,400,200);
	gtk_window_set_title(GTK_WINDOW(window),"login");
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(delete_event),NULL);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(destroy),NULL);
	button=gtk_button_new_with_label("hello world");
	gtk_widget_set_size_request(button,10,10);
	g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_destroy),window);
	gtk_container_add(GTK_CONTAINER(window),button);
	gtk_widget_show(button);
	gtk_widget_show(window);
	gtk_main();
}
int main(int argc, char *argv[])
{
	enter(argc,argv);
	//GtkWidget *window;
	//GtkWidget *button;
	//gtk_init(&argc,&argv);
	//window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//gtk_widget_set_size_request(window,200,100);
	//gtk_window_set_title(GTK_WINDOW(window),"login");
	//g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(delete_event),NULL);
	//g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(destroy),NULL);
	//button=gtk_button_new_with_label("hello world");
	//g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_destroy),window);
	//gtk_container_add(GTK_CONTAINER(window),button);
	//gtk_widget_show(button);
	//gtk_widget_show(window);
	//gtk_main();
	return 0;


}
