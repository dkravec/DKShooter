@echo off
SETLOCAL EnableDelayedExpansion
ECHO .
ECHO ..
ECHO ...
ECHO ....
ECHO #=============[ CLEAN Script ]=============#
ECHO.

:: Get the current folder name
SET "current_folder=%cd%"
FOR %%F IN ("%current_folder%") DO SET "folder_name=%%~nxF"

:: Check if the folder name contains "Lab" or "Assignment" (case-insensitive)
echo %folder_name% | findstr /i "Lab Assignment" >nul

ECHO For "CST 8237 - Game Programming".
ECHO.
ECHO * Only works inside folders with names containing 'Lab' or 'Assignment'.
ECHO.
ECHO WARNING: This script will PERMANENTLY delete everything 
ECHO          inside the directory where this script is located
ECHO          EXCEPT for deliverables (contents to be submitted).
ECHO.
SET /P PROCEED="Are you sure? ('y' to proceed): "

:: If response is other than 'Y/y', skip processing.
ECHO.
IF /I "%PROCEED%" NEQ "Y" GOTO OnConcluded



:: -- PROCEED !

:: Set the list of excluded folders
SET "excluded_folders=Source Config Content .git"

:: Set the list of excluded file extensions (e.g., .uproject)
SET "excluded_extensions=.uproject .bat .gitignore"

:: Delete each DIRECTORY, unless excluded.
ECHO Cleaning [Folders] ...
FOR /d %%D IN (*) DO (
    SET "excluded_folder_found=0"
    :: Check if directory is in our list of "Excluded Folders"
    FOR %%E IN (%excluded_folders%) DO (
        IF /i "%%D"=="%%E" (
            SET "excluded_folder_found=1"
            ECHO * ignoring '%%D' ...
        )
    )
    
    :: Folder NOT found in list of exclusions - Delete it.
    IF !excluded_folder_found! NEQ 1 (
        ECHO DELETE: '%%D'
        rd /s /q "%%D"
        SET "excluded_folder_found="
    )
)
SET "excluded_folder_found="
ECHO.

:: Delete each FILE, unless excluded.
ECHO Cleaning [Files] ...
FOR %%F IN (*) DO (
    SET "excluded_file_found=0"
    :: Check if folder/directory is in our list of "Excluded Folders"
    FOR %%E IN (%excluded_extensions%) DO (
        IF /i "%%~xF"=="%%E" (
            SET "excluded_file_found=1"
            ECHO * ignoring '%%F' ...
        )
    )
    
    :: Folder NOT found in list of exclusions - Delete it.
    IF !excluded_file_found! NEQ 1 (
        ECHO DELETE: '%%F'
        del /q "%%F"
        SET "excluded_file_found="
    )
)
SET "excluded_file_found="
GOTO OnScriptCompleted



:OnScriptCompleted
    ECHO.
    ECHO ... [CLEAN] script completed^^!
    GOTO OnConcluded

:OnError
    ECHO -- ERROR: %error_msg%
    ECHO.
    GOTO ExitWithError



:: Provide a conclusion before exiting.
:OnConcluded
    ECHO.
    ECHO #==========[ END OF SCRIPT ]===========#
    ECHO.
    PAUSE
    ENDLOCAL
    GOTO EOF

:: Exit with error code, if applicable.
:ExitWithError
IF %ERRORLEVEL% NEQ 0 (
    ECHO Exiting script.
    ECHO.
    PAUSE
    EXIT /b
)

:EOF
