/*************************************************************************
  > File Name: toolbar.c  > Author:FENGKAI 
  > Author:FENGKAI 
  > Mail: 763608087@qq.com
  > Created Time: Wed 15 Mar 2017 05:22:40 AM PDT
 ************************************************************************/
#include"./1_2.h"
GtkWidget* ToolBar(GtkWidget*MTbox)//toolbar
{
    GtkWidget *_toolsbar;
    _toolsbar =gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(_toolsbar),GTK_TOOLBAR_ICONS);
    gtk_container_set_border_width(GTK_CONTAINER(_toolsbar),0);
    
gtk_box_pack_start(GTK_BOX(MTbox),_toolsbar,FALSE,FALSE,3);
    return _toolsbar;
}
GtkWidget * StatusBar(GtkWidget*MTbox)
{
    GtkWidget*status;
    status=gtk_statusbar_new();
    gtk_box_pack_end(GTK_BOX(MTbox),status,FALSE,FALSE,1);


}
void menu_pressed()
GtkWidget* CreatMenu(GtkWidget *MTbox)//MenuBar
{
    GtkAccelGroup *accel_group;
    accel_group=gtk_accel_group_new();
    GtkWidget* menubar1;
    menubar1=gtk_menu_bar_new();	
    gtk_box_pack_start(GTK_BOX(MTbox),menubar1,FALSE,FALSE,3);
    GtkWidget*menuitem1;
    menuitem1=gtk_menu_item_new_with_mnemonic("文件(_F)");
    gtk_container_add(GTK_CONTAINER(menubar1),menuitem1);
    GtkWidget*menuitem2;
    menuitem2=gtk_menu_item_new_with_mnemonic("编辑(_C)");
    gtk_container_add(GTK_CONTAINER(menubar1),menuitem2);
    GtkWidget*menuitem1_menu;
    menuitem1_menu=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem1),menuitem1_menu);
    GtkWidget* open1;
    GtkWidget* save1;
    GtkWidget* exit1;
    GtkWidget* close1;
    open1=gtk_menu_item_new_with_mnemonic("打开");
    gtk_container_add(GTK_CONTAINER(menuitem1_menu),open1);
    gtk_widget_add_accelerator(open1,"activate",accel_group,GDK_o,
            (GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

    save1=gtk_menu_item_new_with_mnemonic("保存");
    gtk_container_add(GTK_CONTAINER(menuitem1_menu),save1);
    gtk_widget_add_accelerator(save1,"activate",accel_group,GDK_s,
            (GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

    close1=gtk_menu_item_new_with_mnemonic("退出");
    gtk_container_add(GTK_CONTAINER(menuitem1_menu),close1);
    gtk_widget_add_accelerator(close1,"activate",accel_group,GDK_c,
            (GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

    exit1 =gtk_menu_item_new_with_mnemonic("关闭");
    gtk_container_add(GTK_CONTAINER(menuitem1_menu),exit1);
    gtk_widget_add_accelerator(exit1,"activate",accel_group,GDK_x,
            (GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
    return MTbox;
}

