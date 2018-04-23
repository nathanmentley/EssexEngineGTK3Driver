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
#pragma once

#include <string>

#include <gtk/gtk.h>

#include <EssexEngineCore/BaseDriver.h>
#include <EssexEngineCore/LogDaemon.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineWindowDaemon/IWindowDriver.h>

#include <EssexEngineGTK3Driver/GTK3Window.h>
#include <EssexEngineGTK3Driver/GTK3RenderContext.h>

namespace EssexEngine{
namespace Drivers{
namespace GTK3{
    class GTK3Driver:public Core::Drivers::Base::BaseDriver, public Daemons::Window::IWindowDriver
    {
        public:
            GTK3Driver(WeakPointer<Context> _context);
            ~GTK3Driver();
            
            //IDriver
            void Init() {
                if(GetContext()->HasDaemon<Core::Logging::LogDaemon>()) {
                    GetContext()->GetDaemon<Core::Logging::LogDaemon>()->LogLine(
                        "Loading Driver [%s] [%s]",
                        GetDriverName().c_str(),
                        GetDriverVersion().c_str()
                    );
                }
            }
            
            //IWindowDriver
            void RepaintWindows();
            WeakPointer<Daemons::Window::IWindow> CreateWindow(WeakPointer<Daemons::Window::WindowDef> def);
            void AddButton(WeakPointer<Daemons::Window::IWindow> window, WeakPointer<Daemons::Window::ButtonDef> def);
            void AddLabel(WeakPointer<Daemons::Window::IWindow> window, WeakPointer<Daemons::Window::LabelDef> def);
            WeakPointer<Daemons::Window::IRenderContext> AddCanvas(WeakPointer<Daemons::Window::IWindow> window, WeakPointer<Daemons::Window::CanvasDef> def);
            void RepaintCanvas(WeakPointer<Daemons::Window::IRenderContext> context);
            int GetScreenWidth(WeakPointer<Daemons::Window::IRenderContext> target);
            int GetScreenHeight(WeakPointer<Daemons::Window::IRenderContext> target);
            void CloseWindow(WeakPointer<Daemons::Window::IWindow> window);
            
            //BaseDriver
            std::string GetDriverName() { return "GTK3"; }
            std::string GetDriverVersion() { return ESSEX_ENGINE_VERSION; }
        private:
    };
}}};
