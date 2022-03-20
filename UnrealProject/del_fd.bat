FOR /d /r . %%d IN (".vs") DO @IF EXIST "%%d" rd /s /q "%%d"

FOR /d /r . %%d IN ("Binaries") DO @IF EXIST "%%d" rd /s /q "%%d"

FOR /d /r . %%d IN ("DerivedDataCache") DO @IF EXIST "%%d" rd /s /q "%%d"

FOR /d /r . %%d IN ("Intermediate") DO @IF EXIST "%%d" rd /s /q "%%d"

FOR /d /r . %%d IN ("Saved") DO @IF EXIST "%%d" rd /s /q "%%d"

:: FOR /d /r . %%d IN ("StarterContent") DO @IF EXIST "%%d" rd /s /q "%%d"

del /S *.sln