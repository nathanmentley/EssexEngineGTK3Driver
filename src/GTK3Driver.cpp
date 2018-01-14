/* 
 * Essex Engine
 * 
 * Copyright (C) 2017 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */

#include <EssexEngineGTK3Driver/GTK3Driver.h>

EssexEngine::Drivers::GTK3::GTK3Driver::GTK3Driver(WeakPointer<Context> _context):BaseDriver(_context) {
    gtk_init(NULL,NULL);
}

EssexEngine::Drivers::GTK3::GTK3Driver::~GTK3Driver() {
}

void EssexEngine::Drivers::GTK3::GTK3Driver::RepaintWindows() {
    while(gtk_events_pending()) {
        gtk_main_iteration();
    }
}

//IWIndowDriver
EssexEngine::WeakPointer<EssexEngine::Daemons::Window::IWindow> EssexEngine::Drivers::GTK3::GTK3Driver::CreateWindow(EssexEngine::WeakPointer<EssexEngine::Daemons::Window::WindowDef> def) {
    GtkWindow* window = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(window, def->Title.c_str());
    gtk_window_set_default_size(window, def->Width, def->Height);

    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_widget_destroy), window);
    
    GtkWidget* container = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), container);

    gtk_widget_show_all((GtkWidget*)window);

    return WeakPointer<Daemons::Window::IWindow>(new GTK3Window(window, (GtkFixed*)container));
}

static void gtk_button_callback( GtkWidget *widget, gpointer data) {
    EssexEngine::Daemons::Window::ButtonDef* button = (EssexEngine::Daemons::Window::ButtonDef*)data;

    button->OnClick();
}

void EssexEngine::Drivers::GTK3::GTK3Driver::AddButton(WeakPointer<Daemons::Window::IWindow> window, EssexEngine::WeakPointer<EssexEngine::Daemons::Window::ButtonDef> def) {
    GtkWidget* button = gtk_button_new_with_label(def->Title.c_str());

    g_signal_connect(
        button,
        "clicked",
        G_CALLBACK(gtk_button_callback),
        (gpointer)(def.Get())
    );

    gtk_fixed_put(((GTK3Window*)window.Get())->GetContainer().Get(), button, def->X, def->Y);

    gtk_widget_show_all((GtkWidget*)(((GTK3Window*)window.Get())->GetWindow().Get()));
}

void EssexEngine::Drivers::GTK3::GTK3Driver::AddLabel(WeakPointer<Daemons::Window::IWindow> window, EssexEngine::WeakPointer<EssexEngine::Daemons::Window::LabelDef> def) {
    GtkWidget* button = gtk_button_new_with_label(def->Content.c_str());
    
    gtk_fixed_put(((GTK3Window*)window.Get())->GetContainer().Get(), button, def->X, def->Y);
    
    gtk_widget_show_all((GtkWidget*)(((GTK3Window*)window.Get())->GetWindow().Get()));
}

void EssexEngine::Drivers::GTK3::GTK3Driver::CloseWindow(WeakPointer<Daemons::Window::IWindow> window) {
    gtk_widget_destroy((GtkWidget*)(((GTK3Window*)window.Get())->GetWindow().Get()));
}
