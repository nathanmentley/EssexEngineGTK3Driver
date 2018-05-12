/* 
 * Essex Engine
 * 
 * Copyright (C) 2018 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */

#include <EssexEngineGTK3Driver/GTK3Driver.h>

using EssexEngine::WeakPointer;

using EssexEngine::Daemons::Input::MouseEventLocation;
using EssexEngine::Daemons::Input::KeyboardButton::InputKeys;
using EssexEngine::Daemons::Input::MouseButton::MouseButtons;

using EssexEngine::Daemons::Window::IRenderContext;
using EssexEngine::Daemons::Window::IWindow;
using EssexEngine::Daemons::Window::WindowDef;
using EssexEngine::Daemons::Window::LabelDef;
using EssexEngine::Daemons::Window::ButtonDef;
using EssexEngine::Daemons::Window::CanvasDef;

using EssexEngine::Drivers::GTK3::GTK3Driver;

GTK3Driver::GTK3Driver(WeakPointer<Context> _context):BaseDriver(_context) {
    gtk_init(NULL,NULL);
}

GTK3Driver::~GTK3Driver() {
}

void GTK3Driver::RepaintWindows() {
    while(gtk_events_pending()) {
        gtk_main_iteration();
    }
}

static void gtk_window_callback(GtkWidget *widget, gpointer data) {
    WindowDef* window = (WindowDef*)data;

    window->OnClose();
}

//IWIndowDriver
WeakPointer<IWindow> GTK3Driver::CreateWindow(WeakPointer<WindowDef> def) {
    GtkWindow* window = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(window, def->Title.c_str());
    gtk_window_set_default_size(window, def->Width, def->Height);

    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_window_callback), (gpointer)(def.Get()));
    
    GtkWidget* container = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), container);

    gtk_widget_show_all((GtkWidget*)window);

    return WeakPointer<IWindow>(new GTK3Window(window, (GtkFixed*)container));
}

static void gtk_button_callback(GtkWidget *widget, gpointer data) {
    ButtonDef* button = (ButtonDef*)data;

    button->OnClick();
}

void GTK3Driver::AddButton(WeakPointer<IWindow> window, WeakPointer<ButtonDef> def) {
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

void GTK3Driver::AddLabel(WeakPointer<IWindow> window, WeakPointer<LabelDef> def) {
    GtkWidget* label = gtk_label_new(def->Content.c_str());
    
    gtk_fixed_put(((GTK3Window*)window.Get())->GetContainer().Get(), label, def->X, def->Y);
    
    gtk_widget_show_all((GtkWidget*)(((GTK3Window*)window.Get())->GetWindow().Get()));
}

WeakPointer<IRenderContext> GTK3Driver::AddCanvas(WeakPointer<IWindow> window, WeakPointer<CanvasDef> def) {
    WeakPointer<GtkDrawingArea> image = WeakPointer<GtkWidget>(gtk_drawing_area_new()).Cast<GtkDrawingArea>();
    
    gtk_fixed_put(((GTK3Window*)window.Get())->GetContainer().Get(), image.Cast<GtkWidget>().Get(), def->X, def->Y);
    
    gtk_widget_show_all((GtkWidget*)(((GTK3Window*)window.Get())->GetWindow().Get()));
    
    return WeakPointer<GTK3RenderContext>(new GTK3RenderContext(image, def->Width, def->Height)).Cast<IRenderContext>();
}

void GTK3Driver::RepaintCanvas(WeakPointer<IRenderContext> context) {
}

int GTK3Driver::GetScreenWidth(WeakPointer<IRenderContext> context) {
    return context.Cast<GTK3RenderContext>()->GetWidth();
}

int GTK3Driver::GetScreenHeight(WeakPointer<IRenderContext> context) {
    return context.Cast<GTK3RenderContext>()->GetHeight();
}

void GTK3Driver::CloseWindow(WeakPointer<IWindow> window) {
    gtk_widget_destroy((GtkWidget*)(((GTK3Window*)window.Get())->GetWindow().Get()));
}

//IInputDriver
bool GTK3Driver::IsKeyPressed(WeakPointer<IRenderContext> context, InputKeys key) {
    return false;
}

bool GTK3Driver::IsMousePressed(WeakPointer<IRenderContext> context, MouseButtons key,  MouseEventLocation &data) {
    return false;
}
