#include "../inc/client.h"

static void load_providers()
{
    t_providers.styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(t_providers.styles, "client/data/css/styles.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    if(t_account.theme == 1) { 
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_light.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else if(t_account.theme == 2) {
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_default.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else if(t_account.theme == 3) { 
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_dark.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }

    if(t_account.theme == 1) { 
        t_providers.chat = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg1.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else if(t_account.theme == 2) {
        t_providers.chat = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg1.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else if(t_account.theme == 3) { 
        t_providers.chat = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg1.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);                             // Initializing GTK
    SDL_Init(SDL_INIT_AUDIO);                           // Initializing SDL
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);  // Initializing SDL Mixer
    
    t_application.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);                                 // Creating main window
    gtk_window_set_title(GTK_WINDOW(t_application.window), "PokeChat");                         // Setting window title
    gtk_window_set_default_size(GTK_WINDOW(t_application.window), WINDOW_WIDTH, WINDOW_HEIGHT); // Setting window size
    gtk_window_set_position(GTK_WINDOW(t_application.window), GTK_WIN_POS_CENTER);              // Setting window start position
    gtk_window_set_resizable(GTK_WINDOW(t_application.window), FALSE);                          // Disabling window resize

    GdkPixbuf *icon = create_pixbuf("client/data/images/logo.png");                 // Creating icon for window tab (windows only)
    gtk_window_set_icon(GTK_WINDOW(t_application.window), icon);                    // Setting icon to window
    
    load_providers();   // Loading chosen CSS providers
    GtkWidget *main_area = gtk_fixed_new();                                         // Creating main area
    gtk_container_add(GTK_CONTAINER(t_application.window), main_area);              // Applying main area to current window
    gtk_widget_set_size_request(GTK_WIDGET(main_area), WINDOW_WIDTH, WINDOW_HEIGHT);// Setting size

    build_authorization(&main_area); // Закомиентируй это и разкомментируй все ниже, чтобы получить доступ к непосредственно к чату

    // fill_pokemon();     // Filling random data on home tab
    // test_autofill();    // Заполнение данных аккаунта

    // t_leftbar.active = 1;   // Active button in leftbar
    // build_all(&main_area);  // Main builder function

    gtk_widget_show_all(t_application.window);          // Showing window
    // gtk_widget_hide(GTK_WIDGET(t_leftbar.msg_scr));     // Hiding messanger tab
    // gtk_widget_hide(GTK_WIDGET(t_leftbar.settings_scr));// Hiding settings tab

    g_signal_connect(t_application.window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // When window is closed - exit program
    gtk_main();             // Looping program
    g_object_unref(icon);   // Destroying icon
    Mix_CloseAudio();       // Closing SDL Mixer
    SDL_Quit();             // Closing SDL
    free(tm_struct);        // Freeing time&date struct

    return 0;
}
