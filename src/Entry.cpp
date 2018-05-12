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

using EssexEngine::Context;
using EssexEngine::WeakPointer;

using EssexEngine::Drivers::GTK3::GTK3Driver;
using EssexEngine::Daemons::Window::IWindowDriver;
using EssexEngine::Daemons::Input::IInputDriver;

extern "C" {
    void driver_init(WeakPointer<Context> context) {
        WeakPointer<GTK3Driver> driver = (new GTK3Driver(context));
        
        context->RegisterDriver<IWindowDriver>(
            driver.Cast<IWindowDriver>()
        );
        context->RegisterDriver<IInputDriver>(
            driver.Cast<IInputDriver>()
        );
    }
}
