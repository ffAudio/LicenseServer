/*
 ==============================================================================

 Copyright 2022 Foleys Finest Audio and the contributors

 MIT License
 ===========

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 ==============================================================================
 */

#pragma once

#include "Connection.h"


namespace licensing
{

enum class Status
{
    Unknown = 0,     //< No check yet
    Offline,         //< No license file and server unreachable
    Demo,            //< Demo period currently running
    DemoExpired,     //< Was demoed and demo expired
    LicenseMismatch, //< A license was found but doesn't belong to this machine ID
    Licensed         //< Valid license was found
};

class Unlocker
{
public:
    /*!
     Create an unlocker object that will communicate with a server at the given address
     */
    Unlocker();

    /*!
     Set the license file location. This will try to read and decrypt the license file.
     If it is not there, it tries asynchronously to get a license online.
     */
    void setLicenseFile (const juce::File& filename);

    /*!
     Connect to the server and request a demo
     */
    void requestDemo();

    bool isValidToRun();

    Status getLicenseStatus() const;

    void launchProductPage();

    bool validateLicenseFile (const juce::File& file);

private:
    Connection  connection;

    Status      status = Status::Unknown;
    juce::File  licenseFile;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Unlocker)
};

} // namespace licensing
