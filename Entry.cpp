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

extern "C" {
    void driver_init(EssexEngine::Context* context) {
        EssexEngine::Drivers::GTK3::GTK3Driver* gtk3Driver = new EssexEngine::Drivers::GTK3::GTK3Driver(context);
        
        context->RegisterDriver<EssexEngine::Daemons::Window::IWindowDriver>(gtk3Driver);
    }
}