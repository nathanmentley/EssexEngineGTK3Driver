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
#include <EssexEngineCore/Context.h>
#include <EssexEngineWindowDaemon/IWindowDriver.h>

#include <EssexEngineGTK3Driver/GTK3Window.h>

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
            if(GetContext()->HasDriver<Core::Logging::ILogDriver>()) {
                GetContext()->GetDriver<Core::Logging::ILogDriver>()->LogLine(
                    "Loading Driver [%s] [%s]",
                    GetDriverName().c_str(),
                    GetDriverVersion().c_str()
                );
            }
        }
        
        //IWindowDriver
        void RepaintWindows();
        UniquePointer<Daemons::Window::IWindow> CreateWindow(Daemons::Window::WindowDef def);
        void AddButton(SmartPointer<Daemons::Window::IWindow> window, Daemons::Window::ButtonDef def);
        void AddLabel(SmartPointer<Daemons::Window::IWindow> window, Daemons::Window::LabelDef def);
        void CloseWindow(SmartPointer<Daemons::Window::IWindow> window);
        
        //BaseDriver
        std::string GetDriverName() { return "GTK3"; }
        std::string GetDriverVersion() { return ESSEX_ENGINE_VERSION; }
    private:
    };
}}};