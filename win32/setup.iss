[Setup]
AppName=PL/Stupid Compiler
AppVersion=0.0
AppPublisher=d0p1
AppPublisherURL=https://d0p1.eu/
AppCopyright=Copyright (C) 2023 d0p1
AppSupportURL=https://github.com/d0p1s4m4/PLSc/issues
AppUpdatesURL=https://github.com/d0p1s4m4/PLSc/releases

LicenseFile=..\LICENSE

OutputBaseFilename=plsc-install
OutputDir=..\

WizardStyle=modern

DefaultDirName={autopf}\PLSc
DefaultGroupName=PLSc

UninstallDisplayIcon={app}\plsc.exe

Compression=lzma2
SolidCompression=yes

ChangesAssociations=yes
ChangesEnvironment=yes

[Files]
Source: "..\plsc.exe"; DestDir: "{app}"; DestName: "plsc.exe"

[Icons]
Name: "{group}\PLSc"; Filename: "{app}\plsc.exe"
