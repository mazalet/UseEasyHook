﻿using System;

namespace CreateProcessHookLib.Win32.Model
{
    public struct ProcessInformation
    {
        public IntPtr HProcess;
        public IntPtr HThread;
        public uint DwProcessId;
        public uint DwThreadId;
    }
}