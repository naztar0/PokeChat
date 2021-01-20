#include "../inc/client.h"

static void s_click(GtkWidget *widget) {
    gtk_widget_destroy(GTK_WIDGET(widget));
}

static void s2_click(GtkWidget *widget) {
    if(widget) {}
}

static void remove_person(GtkWidget *widget, gpointer user_id) {
    printf("-- %d\n", (int)(intptr_t)user_id);
    gtk_widget_destroy(GTK_WIDGET(widget));
    new_group->count = new_group->count - 1;
    int *temp = malloc(sizeof(int*) * new_group->count);
    for (int i = 0, j = 0; i < new_group->count + 1; i++)
        if (new_group->users_id[i] != (int)(intptr_t)user_id)
            temp[j++] = new_group->users_id[i];
    free(new_group->users_id);
    new_group->users_id = malloc(sizeof(int*) * new_group->count);
    for (int i = 0; i < new_group->count; i++)
        new_group->users_id[i] = temp[i];
    free(temp);
}

static GtkWidget *create_single_person(char *name, int avatar_id) {
    GtkWidget *single_event = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(single_event), "crlist_person");
    gtk_event_box_set_above_child(GTK_EVENT_BOX(single_event), TRUE);

    GtkWidget *single = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(single), "crlist_person_h");
    gtk_container_add(GTK_CONTAINER(single_event), single);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 34, 34);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (gpointer)(intptr_t)avatar_id);   // Получить avatar пользовтеля
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(single), avatar, FALSE, FALSE, 6);

    GtkWidget *nickname = gtk_label_new(name);                        // Получить username пользователя
    gtk_widget_set_name(GTK_WIDGET(nickname), "nickname");                 // Имя
    gtk_box_pack_start(GTK_BOX(single), nickname, FALSE, FALSE, 5);

    return single_event;
}

static void add_person(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)new_group->search_field)));
        if(name != NULL)
            name = mx_del_extra_spaces(name);
        if(!strcmp(name, "") || !strcmp(name, " ")) 
            return;

        // проверить имя пользователя name на существование
        printf("Username: %s\n", name);
        int avatar = 0, user_id = 0;
        if (!add_user_to_group(name, &user_id, &avatar))
            return;

        gtk_entry_set_text(GTK_ENTRY(new_group->search_field), "");
        GtkWidget *single = create_single_person(name, avatar);
        gtk_box_pack_start(GTK_BOX(t_msg.crlist), single, FALSE, FALSE, 0);
        gtk_widget_show_all(GTK_WIDGET(t_msg.crlist));

        g_signal_connect(G_OBJECT(single), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(single), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
        g_signal_connect(G_OBJECT(single), "button_press_event", G_CALLBACK(remove_person), (gpointer)(intptr_t)user_id); // TODO
    }
}

static void create_group_button_click(GtkWidget *widget, t_new_group *group) {
    if(widget) {}
    GList *parent = gtk_container_get_children(GTK_CONTAINER(t_msg.crlist));
    while(parent != NULL) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
        GList *children2 = gtk_container_get_children(GTK_CONTAINER(children->data));
        children2 = children2->next;
        char* chosen = (char*)gtk_label_get_text(GTK_LABEL(children2->data));
        printf("Found: %s\n", chosen);
        parent = parent->next;
    }
    create_group(group);
}

void creator_group(GtkWidget *main)
{
    t_msg.background = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_msg.background), "crgroup");
    gtk_widget_set_size_request(GTK_WIDGET(t_msg.background), WINDOW_WIDTH-67, WINDOW_HEIGHT);
    g_signal_connect(G_OBJECT(t_msg.background), "button_press_event", G_CALLBACK(s_click), NULL);
    gtk_fixed_put(GTK_FIXED(main), t_msg.background, 0, 0);

    GtkWidget *clickable = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(clickable), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(clickable), "button_press_event", G_CALLBACK(s2_click), NULL);
    gtk_container_add(GTK_CONTAINER(t_msg.background), clickable);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(box), "crgroup_box");
    gtk_container_add(GTK_CONTAINER(clickable), box);

    GtkWidget *title = gtk_label_new("CREATE GROUP");
    gtk_widget_set_name(GTK_WIDGET(title), "creategroup_title");
    gtk_widget_set_halign(title, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), title, FALSE, FALSE, 0);

    //
    GtkWidget *search_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(search_block), "crgroup_search_block");
    gtk_widget_set_size_request(GTK_WIDGET(search_block), 350, 40);
    gtk_box_pack_start(GTK_BOX(box), search_block, FALSE, TRUE, 15);
    GtkWidget *search_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(search_field), "crgroup_search_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Add some people...");
    gtk_entry_set_max_length(GTK_ENTRY(search_field), 10);
    gtk_box_pack_start(GTK_BOX(search_block), search_field, TRUE, TRUE, 0);
    GtkWidget *adduser = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(adduser), "adduser");
    gtk_widget_set_size_request(GTK_WIDGET(adduser), 22, 22);
    gtk_box_pack_start(GTK_BOX(search_block), adduser, FALSE, FALSE, 10);
    gtk_widget_set_halign(GTK_WIDGET(adduser), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(adduser), GTK_ALIGN_CENTER);

    new_group = malloc(sizeof(t_new_group));
    new_group->search_field = search_field;
    new_group->count = 0;
    new_group->users_id = NULL;

    g_signal_connect(G_OBJECT(adduser), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(adduser), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(adduser), "button_press_event", G_CALLBACK(add_person), NULL);
    //

    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 416, 260);
    gtk_box_pack_start(GTK_BOX(box), scrollable, FALSE, FALSE, 0);

    t_msg.crlist = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_widget_set_name(GTK_WIDGET(t_msg.crlist), "crlist");
    gtk_container_add(GTK_CONTAINER(scrollable), t_msg.crlist);

    GtkWidget *create_group_button = gtk_button_new_with_label("Create group");
    gtk_widget_set_name(GTK_WIDGET(create_group_button), "apply_button");
    gtk_button_set_relief(GTK_BUTTON(create_group_button), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(create_group_button), 100, 10);
    gtk_box_pack_start(GTK_BOX(box), create_group_button, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(create_group_button), "clicked", G_CALLBACK(create_group_button_click), NULL);

    gtk_widget_show_all(GTK_WIDGET(t_msg.background));
}
