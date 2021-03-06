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
#pragma once

#include <gtk/gtk.h>

#include <EssexEngineWindowDaemon/IWindow.h>

namespace EssexEngine{
namespace Drivers{
namespace GTK3{
    class GTK3Window: public Daemons::Window::IWindow
    {
        public:
            GTK3Window(GtkWindow* _window, GtkFixed* _container) {
                window = _window;
                container = _container;
            }
            ~GTK3Window() {
                gtk_widget_destroy((GtkWidget*)window.Get());
            }
            
            WeakPointer<GtkWindow> GetWindow() {
                return window;
            }
            
            WeakPointer<GtkFixed> GetContainer() {
                return container;
            }
        private:
            WeakPointer<GtkWindow> window;
            WeakPointer<GtkFixed> container;
    };
}}};
